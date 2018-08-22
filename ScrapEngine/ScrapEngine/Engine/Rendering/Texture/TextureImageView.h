#pragma once

#include <vulkan/vulkan.h>

namespace ScrapEngine {

	class TextureImageView
	{
	private:
		VkImageView textureImageView;

		VkDevice deviceRef;
	public:
		TextureImageView(VkDevice input_deviceRef, VkImage textureImage, uint32_t mipLevelsData);
		~TextureImageView();

		static VkImageView createImageView(VkDevice input_deviceRef, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevelsData);
		VkImageView getTextureImageView() const;
	};

}

