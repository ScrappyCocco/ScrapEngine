#include "VulkanColorResources.h"
#include "TextureImage.h"
#include "TextureImageView.h"

ScrapEngine::Render::VulkanColorResources::VulkanColorResources(vk::SampleCountFlagBits msaaSamples, ScrapEngine::Render::VulkanSwapChain* swapChainRef)
{
	vk::Format colorFormat = swapChainRef->getSwapChainImageFormat();

	ScrapEngine::Render::TextureImage::createImage(swapChainRef->getSwapChainExtent().width, swapChainRef->getSwapChainExtent().height, colorFormat, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal, colorImage, colorImageMemory, 1, msaaSamples);
	colorImageView = ScrapEngine::Render::TextureImageView::createImageView(&colorImage, colorFormat, vk::ImageAspectFlagBits::eColor, 1);

	ScrapEngine::Render::TextureImage::transitionImageLayout(&colorImage, colorFormat, vk::ImageLayout::eUndefined, vk::ImageLayout::eColorAttachmentOptimal, 1);
}


ScrapEngine::Render::VulkanColorResources::~VulkanColorResources()
{
	VulkanDevice::StaticLogicDeviceRef->destroyImageView(colorImageView);
	VulkanDevice::StaticLogicDeviceRef->destroyImage(colorImage);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(colorImageMemory);
}

vk::Image* ScrapEngine::Render::VulkanColorResources::getColorImage()
{
	return &colorImage;
}

vk::ImageView* ScrapEngine::Render::VulkanColorResources::getColorImageView()
{
	return &colorImageView;
}
