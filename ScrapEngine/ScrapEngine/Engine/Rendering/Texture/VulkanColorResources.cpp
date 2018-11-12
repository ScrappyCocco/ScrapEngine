#include "VulkanColorResources.h"
#include "TextureImage.h"
#include "TextureImageView.h"

ScrapEngine::VulkanColorResources::VulkanColorResources(vk::SampleCountFlagBits msaaSamples, ScrapEngine::VulkanSwapChain* swapChainRef)
{
	vk::Format colorFormat = swapChainRef->getSwapChainImageFormat();

	ScrapEngine::TextureImage::createImage(swapChainRef->getSwapChainExtent().width, swapChainRef->getSwapChainExtent().height, colorFormat, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal, colorImage, colorImageMemory, 1, msaaSamples);
	colorImageView = ScrapEngine::TextureImageView::createImageView(&colorImage, colorFormat, vk::ImageAspectFlagBits::eColor, 1);

	ScrapEngine::TextureImage::transitionImageLayout(&colorImage, colorFormat, vk::ImageLayout::eUndefined, vk::ImageLayout::eColorAttachmentOptimal, 1);
}


ScrapEngine::VulkanColorResources::~VulkanColorResources()
{
	VulkanDevice::StaticLogicDeviceRef->destroyImageView(colorImageView);
	VulkanDevice::StaticLogicDeviceRef->destroyImage(colorImage);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(colorImageMemory);
}

vk::Image* ScrapEngine::VulkanColorResources::getColorImage()
{
	return &colorImage;
}

vk::ImageView* ScrapEngine::VulkanColorResources::getColorImageView()
{
	return &colorImageView;
}
