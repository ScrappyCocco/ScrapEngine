#include "VulkanImageView.h"
#include "../Texture/TextureImageView.h"

ScrapEngine::VulkanImageView::VulkanImageView(VkDevice input_deviceRef, ScrapEngine::VulkanSwapChain* SwapChainRef)
	: deviceRef(input_deviceRef)
{
	const std::vector<VkImage>* swapChainImages = SwapChainRef->getSwapChainImagesVector();
	swapChainImageViews.resize(swapChainImages->size());

	for (uint32_t i = 0; i < swapChainImages->size(); i++) {
		swapChainImageViews[i] = TextureImageView::createImageView(input_deviceRef, (*swapChainImages)[i], SwapChainRef->getSwapChainImageFormat(), VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}
}

ScrapEngine::VulkanImageView::~VulkanImageView()
{
	for (auto imageView : swapChainImageViews) {
		vkDestroyImageView(deviceRef, imageView, nullptr);
	}
}

const std::vector<VkImageView>* ScrapEngine::VulkanImageView::getSwapChainImageViewsVector()
{
	return &swapChainImageViews;
}
