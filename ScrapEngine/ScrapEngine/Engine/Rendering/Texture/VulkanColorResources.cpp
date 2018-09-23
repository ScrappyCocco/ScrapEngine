#include "VulkanColorResources.h"
#include "TextureImage.h"
#include "TextureImageView.h"

ScrapEngine::VulkanColorResources::VulkanColorResources(vk::Device* input_deviceRef, vk::PhysicalDevice* input_PhysicalDeviceRef, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, vk::SampleCountFlagBits msaaSamples, ScrapEngine::VulkanSwapChain* swapChainRef)
	: deviceRef(input_deviceRef)
{
	vk::Format colorFormat = swapChainRef->getSwapChainImageFormat();

	ScrapEngine::TextureImage::createImage(deviceRef, input_PhysicalDeviceRef, swapChainRef->getSwapChainExtent().width, swapChainRef->getSwapChainExtent().height, colorFormat, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal, colorImage, colorImageMemory, 1, msaaSamples);
	colorImageView = ScrapEngine::TextureImageView::createImageView(deviceRef, &colorImage, colorFormat, vk::ImageAspectFlagBits::eColor, 1);

	ScrapEngine::TextureImage::transitionImageLayout(deviceRef, &colorImage, colorFormat, vk::ImageLayout::eUndefined, vk::ImageLayout::eColorAttachmentOptimal, CommandPool, graphicsQueue, 1);
}


ScrapEngine::VulkanColorResources::~VulkanColorResources()
{
	deviceRef->destroyImageView(colorImageView);
	deviceRef->destroyImage(colorImage);
	deviceRef->freeMemory(colorImageMemory);
}

vk::Image* ScrapEngine::VulkanColorResources::getColorImage()
{
	return &colorImage;
}

vk::ImageView* ScrapEngine::VulkanColorResources::getColorImageView()
{
	return &colorImageView;
}
