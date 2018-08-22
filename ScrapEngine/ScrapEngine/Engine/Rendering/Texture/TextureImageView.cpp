#include "TextureImageView.h"

#include <stdexcept>

ScrapEngine::TextureImageView::TextureImageView(VkDevice input_deviceRef, VkImage textureImage, uint32_t mipLevelsData)
	: deviceRef(input_deviceRef)
{
	textureImageView = createImageView(deviceRef, textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, mipLevelsData);
}

ScrapEngine::TextureImageView::~TextureImageView()
{
	vkDestroyImageView(deviceRef, textureImageView, nullptr);
}

VkImageView ScrapEngine::TextureImageView::createImageView(VkDevice input_deviceRef, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevelsData) {
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = mipLevelsData;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(input_deviceRef, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture image view!");
	}

	return imageView;
}

VkImageView ScrapEngine::TextureImageView::getTextureImageView() const
{
	return textureImageView;
}
