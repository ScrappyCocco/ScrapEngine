#include "VulkanDepthResources.h"

#include "../Texture/TextureImage.h"
#include "../Texture/TextureImageView.h"

ScrapEngine::VulkanDepthResources::VulkanDepthResources(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDeviceRef, VkCommandPool CommandPool, VkQueue graphicsQueue, const VkExtent2D* swapChainExtent, VkSampleCountFlagBits msaaSamples)
	: deviceRef(input_deviceRef)
{
	VkFormat depthFormat = findDepthFormat(PhysicalDeviceRef);

	TextureImage::createImage(deviceRef, PhysicalDeviceRef, swapChainExtent->width, swapChainExtent->height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory, 1, msaaSamples);
	depthImageView = TextureImageView::createImageView(deviceRef, depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);

	TextureImage::transitionImageLayout(deviceRef, depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, CommandPool, graphicsQueue, 1);
}


ScrapEngine::VulkanDepthResources::~VulkanDepthResources()
{
	vkDestroyImageView(deviceRef, depthImageView, nullptr);
	vkDestroyImage(deviceRef, depthImage, nullptr);
	vkFreeMemory(deviceRef, depthImageMemory, nullptr);
}

VkFormat ScrapEngine::VulkanDepthResources::findSupportedFormat(VkPhysicalDevice PhysicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(PhysicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}

VkFormat ScrapEngine::VulkanDepthResources::findDepthFormat(VkPhysicalDevice PhysicalDevice)
{
	return findSupportedFormat(PhysicalDevice, 
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

bool ScrapEngine::VulkanDepthResources::hasStencilComponent(VkFormat format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;;
}

VkImage ScrapEngine::VulkanDepthResources::getDepthImage() const
{
	return depthImage;
}

VkDeviceMemory ScrapEngine::VulkanDepthResources::getDepthImageMemory() const
{
	return depthImageMemory;
}

VkImageView ScrapEngine::VulkanDepthResources::getDepthImageView()
{
	return depthImageView;
}
