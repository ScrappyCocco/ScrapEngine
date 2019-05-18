#include "VulkanSwapChain.h"

#include <algorithm>
#include "../Base/StaticTypes.h"

ScrapEngine::Render::VulkanSwapChain::VulkanSwapChain(SwapChainSupportDetails swapChainSupport, GraphicsQueue::QueueFamilyIndices indices, vk::SurfaceKHR* input_surfaceRef, const uint32_t& WIDTH, const uint32_t& HEIGHT, bool vsync)
	: surfaceRef(input_surfaceRef)
{
	vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes, vsync);
	vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities, WIDTH, HEIGHT);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	vk::SwapchainCreateInfoKHR createInfo(
		vk::SwapchainCreateFlagsKHR(),
		*surfaceRef,
		imageCount,
		surfaceFormat.format,
		surfaceFormat.colorSpace,
		extent,
		1,
		vk::ImageUsageFlagBits::eColorAttachment
	);

	uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.setImageSharingMode(vk::SharingMode::eConcurrent);
		createInfo.setQueueFamilyIndexCount(2);
		createInfo.setPQueueFamilyIndices(queueFamilyIndices);
	}
	else {
		createInfo.setImageSharingMode(vk::SharingMode::eExclusive);
	}

	createInfo.setPreTransform(swapChainSupport.capabilities.currentTransform);
	createInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
	createInfo.setPresentMode(presentMode);
	createInfo.setClipped(true);

	if (VulkanDevice::StaticLogicDeviceRef->createSwapchainKHR(&createInfo, nullptr, &swapChain) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanSwapChain: Failed to create swap chain!");
	}

	VulkanDevice::StaticLogicDeviceRef->getSwapchainImagesKHR(swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	VulkanDevice::StaticLogicDeviceRef->getSwapchainImagesKHR(swapChain, &imageCount, swapChainImages.data());

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}

ScrapEngine::Render::VulkanSwapChain::~VulkanSwapChain()
{
	VulkanDevice::StaticLogicDeviceRef->destroySwapchainKHR(swapChain);
}

vk::SurfaceFormatKHR ScrapEngine::Render::VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == vk::Format::eUndefined) {
		return { vk::Format::eB8G8R8A8Unorm , vk::ColorSpaceKHR::eSrgbNonlinear};
	}

	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == vk::Format::eB8G8R8A8Unorm  && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

vk::PresentModeKHR ScrapEngine::Render::VulkanSwapChain::chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes, bool vsync)
{
	vk::PresentModeKHR bestMode = vk::PresentModeKHR::eFifo;

	for (const auto& availablePresentMode : availablePresentModes) {
		if (vsync && (availablePresentMode == vk::PresentModeKHR::eFifoRelaxed || availablePresentMode == vk::PresentModeKHR::eFifo)) {
			return availablePresentMode;
		}
		if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
			return availablePresentMode;
		}
		else if (availablePresentMode == vk::PresentModeKHR::eImmediate) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}

vk::Extent2D ScrapEngine::Render::VulkanSwapChain::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const uint32_t& WIDTH, const uint32_t& HEIGHT)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actualExtent = { WIDTH, HEIGHT };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

vk::SwapchainKHR ScrapEngine::Render::VulkanSwapChain::getSwapChain() const
{
	return swapChain;
}

const std::vector<vk::Image>* ScrapEngine::Render::VulkanSwapChain::getSwapChainImagesVector()
{
	return &swapChainImages;
}

vk::Format ScrapEngine::Render::VulkanSwapChain::getSwapChainImageFormat() const
{
	return swapChainImageFormat;
}

vk::Extent2D ScrapEngine::Render::VulkanSwapChain::getSwapChainExtent() const
{
	return swapChainExtent;
}
