#include "VulkanColorResources.h"
#include "TextureImage.h"
#include "TextureImageView.h"

ScrapEngine::VulkanColorResources::VulkanColorResources(VkDevice input_deviceRef, VkPhysicalDevice input_PhysicalDeviceRef, VkCommandPool CommandPool, VkQueue graphicsQueue, VkSampleCountFlagBits msaaSamples, ScrapEngine::VulkanSwapChain* swapChainRef) 
	: deviceRef(input_deviceRef)
{
	VkFormat colorFormat = swapChainRef->getSwapChainImageFormat();

	ScrapEngine::TextureImage::createImage(deviceRef, input_PhysicalDeviceRef, swapChainRef->getSwapChainExtent().width, swapChainRef->getSwapChainExtent().height, colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, colorImage, colorImageMemory, 1, msaaSamples);
	colorImageView = ScrapEngine::TextureImageView::createImageView(deviceRef, colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);

	ScrapEngine::TextureImage::transitionImageLayout(deviceRef, colorImage, colorFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, CommandPool, graphicsQueue, 1);
}


ScrapEngine::VulkanColorResources::~VulkanColorResources()
{
	vkDestroyImageView(deviceRef, colorImageView, nullptr);
	vkDestroyImage(deviceRef, colorImage, nullptr);
	vkFreeMemory(deviceRef, colorImageMemory, nullptr);
}

VkImage ScrapEngine::VulkanColorResources::getColorImage() const
{
	return colorImage;
}

VkImageView ScrapEngine::VulkanColorResources::getColorImageView() const
{
	return colorImageView;
}
