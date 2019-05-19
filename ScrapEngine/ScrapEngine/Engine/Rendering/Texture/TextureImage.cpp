#define STB_IMAGE_IMPLEMENTATION
#include <Engine/Rendering/Texture/TextureImage.h>

#include <stdexcept>
#include <Engine/Rendering/Memory/MemoryManager.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>

ScrapEngine::Render::TextureImage::TextureImage(const std::string& file_path, bool should_copy_from_staging)
{
	stbi_uc* pixels = stbi_load(file_path.c_str(), &tex_width_, &tex_height_, &tex_channels_, STBI_rgb_alpha);

	const vk::DeviceSize image_size = tex_width_ * tex_height_ * 4;
	mip_levels_ = static_cast<uint32_t>(std::floor(std::log2(std::max(tex_width_, tex_height_)))) + 1;

	if (!pixels)
	{
		throw std::runtime_error("TextureImage: Failed to load texture image! (pixels not valid) - " + file_path);
	}

	staginf_buffer_ref_ = new StagingBuffer(image_size, pixels);

	stbi_image_free(pixels);

	create_image(tex_width_, tex_height_, vk::Format::eR8G8B8A8Unorm, vk::ImageTiling::eOptimal,
	             vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::
	             eSampled, vk::MemoryPropertyFlagBits::eDeviceLocal, texture_image_, texture_image_memory_);

	transition_image_layout(&texture_image_, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined,
	                        vk::ImageLayout::eTransferDstOptimal);

	if (should_copy_from_staging)
	{
		StagingBuffer::copy_buffer_to_image(staginf_buffer_ref_->get_staging_buffer(), &texture_image_,
		                                    static_cast<uint32_t>(tex_width_), static_cast<uint32_t>(tex_height_));

		delete staginf_buffer_ref_;
		staginf_buffer_ref_ = nullptr;

		generate_mipmaps(&texture_image_, vk::Format::eR8G8B8A8Unorm, tex_width_, tex_height_, mip_levels_);
	}
}

ScrapEngine::Render::TextureImage::~TextureImage()
{
	delete staginf_buffer_ref_;

	VulkanDevice::static_logic_device_ref->destroyImage(texture_image_);
	VulkanDevice::static_logic_device_ref->freeMemory(texture_image_memory_);
}

void ScrapEngine::Render::TextureImage::create_image(const uint32_t& width, const uint32_t& height,
                                                     const vk::Format& format, vk::ImageTiling tiling,
                                                     const vk::ImageUsageFlags& usage, const vk::MemoryPropertyFlags& properties,
                                                     vk::Image& image, vk::DeviceMemory& image_memory) const
{
	create_image(width, height, format, tiling, usage, properties, image, image_memory, mip_levels_,
	             vk::SampleCountFlagBits::e1);
}

void ScrapEngine::Render::TextureImage::create_image(const uint32_t& width, const uint32_t& height,
                                                     const vk::Format& format, vk::ImageTiling tiling,
                                                     const vk::ImageUsageFlags& usage,
                                                     const vk::MemoryPropertyFlags& properties, vk::Image& image,
                                                     vk::DeviceMemory& image_memory, uint32_t mip_levels_data,
                                                     vk::SampleCountFlagBits num_samples)
{
	vk::ImageCreateInfo image_info(
		vk::ImageCreateFlags(),
		vk::ImageType::e2D,
		format,
		vk::Extent3D(width, height, 1),
		mip_levels_data,
		1,
		num_samples,
		tiling,
		usage,
		vk::SharingMode::eExclusive
	);

	if (VulkanDevice::static_logic_device_ref->createImage(&image_info, nullptr, &image) != vk::Result::eSuccess)
	{
		throw std::runtime_error("TextureImage: Failed to create image!");
	}

	vk::MemoryRequirements mem_requirements;
	VulkanDevice::static_logic_device_ref->getImageMemoryRequirements(image, &mem_requirements);

	vk::MemoryAllocateInfo alloc_info(
		mem_requirements.size,
		find_memory_type(mem_requirements.memoryTypeBits, properties)
	);

	if (VulkanDevice::static_logic_device_ref->allocateMemory(&alloc_info, nullptr, &image_memory) != vk::Result::
		eSuccess)
	{
		throw std::runtime_error("TextureImage: Failed to allocate image memory!");
	}

	VulkanDevice::static_logic_device_ref->bindImageMemory(image, image_memory, 0);
}

void ScrapEngine::Render::TextureImage::transition_image_layout(vk::Image* image, const vk::Format& format,
                                                                const vk::ImageLayout& old_layout,
                                                                const vk::ImageLayout& new_layout) const
{
	transition_image_layout(image, format, old_layout, new_layout, mip_levels_);
}

void ScrapEngine::Render::TextureImage::transition_image_layout(vk::Image* image, const vk::Format& format,
                                                                const vk::ImageLayout& old_layout,
                                                                const vk::ImageLayout& new_layout,
                                                                const uint32_t& mip_levels_data, int layercount)
{
	vk::CommandBuffer* command_buffer = BaseBuffer::begin_single_time_commands();

	vk::ImageMemoryBarrier barrier(vk::AccessFlags(), vk::AccessFlags(), old_layout, new_layout, 0, 0, *image);

	if (new_layout == vk::ImageLayout::eDepthStencilAttachmentOptimal)
	{
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;

		if (VulkanDepthResources::has_stencil_component(format))
		{
			barrier.subresourceRange.aspectMask |= vk::ImageAspectFlagBits::eStencil;
		}
	}
	else
	{
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
	}

	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = mip_levels_data;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = layercount;

	vk::PipelineStageFlags source_stage;
	vk::PipelineStageFlags destination_stage;

	if (old_layout == vk::ImageLayout::eUndefined && new_layout == vk::ImageLayout::eTransferDstOptimal)
	{
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

		source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
		destination_stage = vk::PipelineStageFlagBits::eTransfer;
	}
	else if (old_layout == vk::ImageLayout::eTransferDstOptimal && new_layout == vk::ImageLayout::eShaderReadOnlyOptimal
	)
	{
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

		source_stage = vk::PipelineStageFlagBits::eTransfer;
		destination_stage = vk::PipelineStageFlagBits::eFragmentShader;
	}
	else if (old_layout == vk::ImageLayout::eUndefined && new_layout == vk::ImageLayout::eDepthStencilAttachmentOptimal)
	{
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::
			eDepthStencilAttachmentWrite;

		source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
		destination_stage = vk::PipelineStageFlagBits::eEarlyFragmentTests;
	}
	else if (old_layout == vk::ImageLayout::eUndefined && new_layout == vk::ImageLayout::eColorAttachmentOptimal)
	{
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;
		source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
		destination_stage = vk::PipelineStageFlagBits::eColorAttachmentOutput;
	}
	else
	{
		throw std::invalid_argument("unsupported layout transition!");
	}

	command_buffer->pipelineBarrier(
		source_stage,
		destination_stage,
		vk::DependencyFlags(),
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

	BaseBuffer::end_single_time_commands(command_buffer);
}

void ScrapEngine::Render::TextureImage::generate_mipmaps(vk::Image* image, const vk::Format& image_format,
                                                         const int32_t& tex_width, const int32_t& tex_height,
                                                         const uint32_t& mip_levels)
{
	// Check if image format supports linear blitting
	const vk::FormatProperties format_properties = VulkanDevice::static_physical_device_ref->
		getFormatProperties(image_format);

	if (!(format_properties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eSampledImageFilterLinear))
	{
		throw std::runtime_error("TextureImage: Texture image format does not support linear blitting!");
	}

	vk::CommandBuffer* command_buffer = BaseBuffer::begin_single_time_commands();

	vk::ImageMemoryBarrier barrier(
		vk::AccessFlags(),
		vk::AccessFlags(),
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eUndefined,
		0,
		0,
		*image,
		vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1)
	);

	int32_t mip_width = tex_width;
	int32_t mip_height = tex_height;

	for (uint32_t i = 1; i < mip_levels; i++)
	{
		barrier.subresourceRange.baseMipLevel = i - 1;
		barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		barrier.newLayout = vk::ImageLayout::eTransferSrcOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;

		command_buffer->pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eTransfer,
			vk::DependencyFlags(),
			0, nullptr,
			0, nullptr,
			1, &barrier);
		vk::ImageBlit blit(
			vk::ImageSubresourceLayers(
				vk::ImageAspectFlagBits::eColor,
				i - 1,
				0,
				1),
			std::array<vk::Offset3D, 2>{
				vk::Offset3D(),
				vk::Offset3D(mip_width, mip_height, 1)
			},
			vk::ImageSubresourceLayers(
				vk::ImageAspectFlagBits::eColor,
				i,
				0,
				1),
			std::array<vk::Offset3D, 2>{
				vk::Offset3D(),
				vk::Offset3D(mip_width > 1 ? mip_width / 2 : 1, mip_height > 1 ? mip_height / 2 : 1, 1)
			}
		);

		command_buffer->blitImage(*image, vk::ImageLayout::eTransferSrcOptimal, *image,
		                          vk::ImageLayout::eTransferDstOptimal, 1, &blit, vk::Filter::eLinear);

		barrier.oldLayout = vk::ImageLayout::eTransferSrcOptimal;
		barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

		command_buffer->pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
		                                vk::PipelineStageFlagBits::eFragmentShader, vk::DependencyFlags(), 0, nullptr,
		                                0, nullptr, 1, &barrier);

		if (mip_width > 1) mip_width /= 2;
		if (mip_height > 1) mip_height /= 2;
	}

	barrier.subresourceRange.baseMipLevel = mip_levels - 1;
	barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
	barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
	barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

	command_buffer->pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader,
	                                vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &barrier);

	BaseBuffer::end_single_time_commands(command_buffer);
}

vk::Image* ScrapEngine::Render::TextureImage::get_texture_image()
{
	return &texture_image_;
}

ScrapEngine::Render::StagingBuffer* ScrapEngine::Render::TextureImage::get_texture_staging_buffer() const
{
	return staginf_buffer_ref_;
}

vk::DeviceMemory* ScrapEngine::Render::TextureImage::get_texture_image_memory()
{
	return &texture_image_memory_;
}

uint32_t ScrapEngine::Render::TextureImage::get_mip_levels() const
{
	return mip_levels_;
}

int ScrapEngine::Render::TextureImage::get_texture_width() const
{
	return tex_width_;
}

int ScrapEngine::Render::TextureImage::get_texture_height() const
{
	return tex_height_;
}

int ScrapEngine::Render::TextureImage::get_texture_channels() const
{
	return tex_channels_;
}
