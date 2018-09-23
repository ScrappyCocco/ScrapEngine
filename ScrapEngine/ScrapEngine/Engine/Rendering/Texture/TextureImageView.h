#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {

	class TextureImageView
	{
	private:
		vk::ImageView textureImageView;

		vk::Device* deviceRef;
	public:
		TextureImageView(vk::Device* input_deviceRef, vk::Image* textureImage, uint32_t mipLevelsData);
		~TextureImageView();

		static vk::ImageView createImageView(vk::Device* input_deviceRef, vk::Image* image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData);
		vk::ImageView* getTextureImageView();
	};

}

