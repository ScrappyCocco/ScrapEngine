#define STB_IMAGE_IMPLEMENTATION
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Memory/MemoryManager.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>

ScrapEngine::Render::BaseTexture::~BaseTexture()
{
	VulkanDevice::static_logic_device_ref->destroyImage(texture_image_);
	VulkanDevice::static_logic_device_ref->freeMemory(texture_image_memory_);
}

vk::Image* ScrapEngine::Render::BaseTexture::get_texture_image()
{
	return &texture_image_;
}

vk::DeviceMemory* ScrapEngine::Render::BaseTexture::get_texture_image_memory()
{
	return &texture_image_memory_;
}

uint32_t ScrapEngine::Render::BaseTexture::get_mip_levels() const
{
	return mip_levels_;
}

void ScrapEngine::Render::BaseTexture::create_image(const uint32_t& width, const uint32_t& height,
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

void ScrapEngine::Render::BaseTexture::transition_image_layout(vk::Image* image, const vk::Format& format,
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

void ScrapEngine::Render::BaseTexture::generate_mipmaps(vk::Image* image, const vk::Format& image_format,
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
