#include <Engine/Rendering/Texture/Texture/SkyboxTexture/SkyboxStagingTexture.h>
#include <stdexcept>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>

ScrapEngine::Render::SkyboxStagingTexture::SkyboxStagingTexture(const std::string& file_path)
{
	stbi_uc* pixels = stbi_load(file_path.c_str(), &tex_width_, &tex_height_, &tex_channels_, STBI_rgb_alpha);

	const vk::DeviceSize image_size = tex_width_ * tex_height_ * 4;
	mip_levels_ = static_cast<uint32_t>(std::floor(std::log2(std::max(tex_width_, tex_height_)))) + 1;

	if (!pixels)
	{
		throw std::runtime_error("SkyboxStagingTexture: Failed to load texture image! (pixels not valid) - " + file_path);
	}

	staginf_buffer_ref_ = new ImageStagingBuffer(image_size, pixels);

	stbi_image_free(pixels);
}

ScrapEngine::Render::SkyboxStagingTexture::~SkyboxStagingTexture()
{
	delete staginf_buffer_ref_;
}

ScrapEngine::Render::BaseStagingBuffer* ScrapEngine::Render::SkyboxStagingTexture::get_texture_staging_buffer() const
{
	return staginf_buffer_ref_;
}

int ScrapEngine::Render::SkyboxStagingTexture::get_texture_width() const
{
	return tex_width_;
}

int ScrapEngine::Render::SkyboxStagingTexture::get_texture_height() const
{
	return tex_height_;
}
