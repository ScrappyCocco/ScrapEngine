#include "VulkanDepthResources.h"

#include "../Texture/TextureImage.h"
#include "../Texture/TextureImageView.h"

ScrapEngine::VulkanDepthResources::VulkanDepthResources(const vk::Extent2D* swapChainExtent, vk::SampleCountFlagBits msaaSamples)
{
	vk::Format depthFormat = findDepthFormat();

	TextureImage::createImage(swapChainExtent->width, swapChainExtent->height, depthFormat, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eDepthStencilAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal, depthImage, depthImageMemory, 1, msaaSamples);
	depthImageView = TextureImageView::createImageView(&depthImage, depthFormat, vk::ImageAspectFlagBits::eDepth, 1);

	TextureImage::transitionImageLayout(&depthImage, depthFormat, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal, 1);
}


ScrapEngine::VulkanDepthResources::~VulkanDepthResources()
{
	VulkanDevice::StaticLogicDeviceRef->destroyImageView(depthImageView);
	VulkanDevice::StaticLogicDeviceRef->destroyImage(depthImage);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(depthImageMemory);
}

vk::Format ScrapEngine::VulkanDepthResources::findSupportedFormat(const std::vector<vk::Format>& candidates, vk::ImageTiling tiling, vk::FormatFeatureFlags features)
{
	for (vk::Format format : candidates) {
		vk::FormatProperties props;
		VulkanDevice::StaticPhysicalDeviceRef->getFormatProperties(format, &props);

		if (tiling == vk::ImageTiling::eLinear && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == vk::ImageTiling::eOptimal && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("VulkanDepthResources: Failed to find supported format!");
}

vk::Format ScrapEngine::VulkanDepthResources::findDepthFormat()
{
	return findSupportedFormat(
		{ 
			vk::Format::eD32Sfloat , vk::Format::eD32SfloatS8Uint , vk::Format::eD24UnormS8Uint 
		},
		vk::ImageTiling::eOptimal,
		vk::FormatFeatureFlagBits::eDepthStencilAttachment
	);
}

bool ScrapEngine::VulkanDepthResources::hasStencilComponent(const vk::Format& format)
{
	return format == vk::Format::eD32SfloatS8Uint || format == vk::Format::eD24UnormS8Uint;
}

vk::Image* ScrapEngine::VulkanDepthResources::getDepthImage()
{
	return &depthImage;
}

vk::DeviceMemory* ScrapEngine::VulkanDepthResources::getDepthImageMemory()
{
	return &depthImageMemory;
}

vk::ImageView* ScrapEngine::VulkanDepthResources::getDepthImageView()
{
	return &depthImageView;
}
