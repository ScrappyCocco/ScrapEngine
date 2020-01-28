#define STB_IMAGE_IMPLEMENTATION
#include <Engine/Rendering/Texture/Texture/StandardTexture/StandardTexture.h>
#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::StandardTexture::StandardTexture(const std::string& file_path)
{
	stbi_uc* pixels = stbi_load(file_path.c_str(), &tex_width_, &tex_height_, &tex_channels_, STBI_rgb_alpha);

	const vk::DeviceSize image_size = tex_width_ * tex_height_ * 4;
	mip_levels_ = static_cast<uint32_t>(std::floor(std::log2(std::max(tex_width_, tex_height_)))) + 1;

	if (!pixels)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "TextureImage: Failed to load texture image! (pixels not valid) - " + file_path);
	}

	const std::unique_ptr<BaseStagingBuffer> staginf_buffer_ref =
		std::make_unique<ImageStagingBuffer>(image_size, pixels);

	stbi_image_free(pixels);

	//Create the image

	const vk::ImageCreateInfo image_info(
		vk::ImageCreateFlags(),
		vk::ImageType::e2D,
		vk::Format::eR8G8B8A8Unorm,
		vk::Extent3D(tex_width_, tex_height_, 1),
		mip_levels_,
		1,
		vk::SampleCountFlagBits::e1,
		vk::ImageTiling::eOptimal,
		vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst |
		vk::ImageUsageFlagBits::eSampled,
		vk::SharingMode::eExclusive
	);

	VulkanMemoryAllocator::get_instance()->create_texture_image(&image_info, texture_image_, texture_image_memory_);

	transition_image_layout(&texture_image_, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined,
	                        vk::ImageLayout::eTransferDstOptimal);

	ImageStagingBuffer::copy_buffer_to_image(staginf_buffer_ref->get_staging_buffer(), &texture_image_,
	                                         static_cast<uint32_t>(tex_width_), static_cast<uint32_t>(tex_height_));

	generate_mipmaps(&texture_image_, vk::Format::eR8G8B8A8Unorm, tex_width_, tex_height_, mip_levels_);
}

void ScrapEngine::Render::StandardTexture::transition_image_layout(vk::Image* image, const vk::Format& format,
                                                                   const vk::ImageLayout& old_layout,
                                                                   const vk::ImageLayout& new_layout) const
{
	BaseTexture::transition_image_layout(image, format, old_layout, new_layout, mip_levels_);
}

int ScrapEngine::Render::StandardTexture::get_texture_width() const
{
	return tex_width_;
}

int ScrapEngine::Render::StandardTexture::get_texture_height() const
{
	return tex_height_;
}

int ScrapEngine::Render::StandardTexture::get_texture_channels() const
{
	return tex_channels_;
}
