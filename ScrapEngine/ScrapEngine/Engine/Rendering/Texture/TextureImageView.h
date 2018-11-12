#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {

	class TextureImageView
	{
	private:
		vk::ImageView textureImageView;
	public:
		TextureImageView(vk::Image* textureImage, const uint32_t& mipLevelsData, bool iscubemap = false, int layerCount = 1);
		~TextureImageView();

		static vk::ImageView createImageView(vk::Image* image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData);
		static vk::ImageView createCubeMapImageView(vk::Image* image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData, int layerCount);
		vk::ImageView* getTextureImageView();
	};

}

