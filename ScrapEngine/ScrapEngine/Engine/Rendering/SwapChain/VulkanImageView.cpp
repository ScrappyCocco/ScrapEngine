#include "VulkanImageView.h"
#include "../Texture/TextureImageView.h"

ScrapEngine::VulkanImageView::VulkanImageView(vk::Device* input_deviceRef, ScrapEngine::VulkanSwapChain* SwapChainRef)
	: deviceRef(input_deviceRef)
{
	const std::vector<vk::Image>* swapChainImages = SwapChainRef->getSwapChainImagesVector();
	swapChainImageViews.resize(swapChainImages->size());

	for (uint32_t i = 0; i < swapChainImages->size(); i++) {
		swapChainImageViews[i] = TextureImageView::createImageView(input_deviceRef, const_cast<vk::Image*>(&(*swapChainImages)[i]), SwapChainRef->getSwapChainImageFormat(), vk::ImageAspectFlagBits::eColor, 1);
	}
}

ScrapEngine::VulkanImageView::~VulkanImageView()
{
	for (auto imageView : swapChainImageViews) {
		deviceRef->destroyImageView(imageView);
	}
}

const std::vector<vk::ImageView>* ScrapEngine::VulkanImageView::getSwapChainImageViewsVector()
{
	return &swapChainImageViews;
}
