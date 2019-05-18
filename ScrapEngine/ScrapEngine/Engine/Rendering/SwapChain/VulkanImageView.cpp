#include "VulkanImageView.h"
#include "../Texture/TextureImageView.h"
#include "../Base/StaticTypes.h"

ScrapEngine::Render::VulkanImageView::VulkanImageView(ScrapEngine::Render::VulkanSwapChain* SwapChainRef)
{
	const std::vector<vk::Image>* swapChainImages = SwapChainRef->getSwapChainImagesVector();
	swapChainImageViews.resize(swapChainImages->size());

	for (uint32_t i = 0; i < swapChainImages->size(); i++) {
		swapChainImageViews[i] = TextureImageView::createImageView(const_cast<vk::Image*>(&(*swapChainImages)[i]), SwapChainRef->getSwapChainImageFormat(), vk::ImageAspectFlagBits::eColor, 1);
	}
}

ScrapEngine::Render::VulkanImageView::~VulkanImageView()
{
	for (auto imageView : swapChainImageViews) {
		VulkanDevice::StaticLogicDeviceRef->destroyImageView(imageView);
	}
}

const std::vector<vk::ImageView>* ScrapEngine::Render::VulkanImageView::getSwapChainImageViewsVector()
{
	return &swapChainImageViews;
}
