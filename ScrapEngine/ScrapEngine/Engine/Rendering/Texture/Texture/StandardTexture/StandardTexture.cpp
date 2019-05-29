#define STB_IMAGE_IMPLEMENTATION
#include <Engine/Rendering/Texture/Texture/StandardTexture/StandardTexture.h>
#include <stdexcept>
#include <Engine/Rendering/Memory/MemoryManager.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>

ScrapEngine::Render::StandardTexture::StandardTexture(const std::string& file_path, bool should_copy_from_staging)
{
	stbi_uc* pixels = stbi_load(file_path.c_str(), &tex_width_, &tex_height_, &tex_channels_, STBI_rgb_alpha);

	const vk::DeviceSize image_size = tex_width_ * tex_height_ * 4;
	mip_levels_ = static_cast<uint32_t>(std::floor(std::log2(std::max(tex_width_, tex_height_)))) + 1;

	if (!pixels)
	{
		throw std::runtime_error("TextureImage: Failed to load texture image! (pixels not valid) - " + file_path);
	}

	staginf_buffer_ref_ = new ImageStagingBuffer(image_size, pixels);

	stbi_image_free(pixels);

	create_image(tex_width_, tex_height_, vk::Format::eR8G8B8A8Unorm, vk::ImageTiling::eOptimal,
	             vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::
	             eSampled, vk::MemoryPropertyFlagBits::eDeviceLocal, texture_image_, texture_image_memory_);

	transition_image_layout(&texture_image_, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined,
	                        vk::ImageLayout::eTransferDstOptimal);

	if (should_copy_from_staging)
	{
		ImageStagingBuffer::copy_buffer_to_image(staginf_buffer_ref_->get_staging_buffer(), &texture_image_,
		                                         static_cast<uint32_t>(tex_width_), static_cast<uint32_t>(tex_height_));

		delete staginf_buffer_ref_;
		staginf_buffer_ref_ = nullptr;

		generate_mipmaps(&texture_image_, vk::Format::eR8G8B8A8Unorm, tex_width_, tex_height_, mip_levels_);
	}
}

ScrapEngine::Render::StandardTexture::~StandardTexture()
{
	delete staginf_buffer_ref_;
}

void ScrapEngine::Render::StandardTexture::create_image(const uint32_t& width, const uint32_t& height,
                                                        const vk::Format& format, vk::ImageTiling tiling,
                                                        const vk::ImageUsageFlags& usage,
                                                        const vk::MemoryPropertyFlags& properties,
                                                        vk::Image& image, vk::DeviceMemory& image_memory) const
{
	BaseTexture::create_image(width, height, format, tiling, usage, properties, image, image_memory, mip_levels_,
	                          vk::SampleCountFlagBits::e1);
}


void ScrapEngine::Render::StandardTexture::transition_image_layout(vk::Image* image, const vk::Format& format,
                                                                   const vk::ImageLayout& old_layout,
                                                                   const vk::ImageLayout& new_layout) const
{
	BaseTexture::transition_image_layout(image, format, old_layout, new_layout, mip_levels_);
}

ScrapEngine::Render::BaseStagingBuffer* ScrapEngine::Render::StandardTexture::get_texture_staging_buffer() const
{
	return staginf_buffer_ref_;
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
