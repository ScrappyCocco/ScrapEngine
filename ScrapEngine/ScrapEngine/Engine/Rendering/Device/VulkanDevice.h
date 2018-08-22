#pragma once

#include <vulkan/vulkan.h>
#include "../Instance/VukanInstance.h"
#include "../Window/VulkanSurface.h"
#include "../../Debug/DebugLog.h"
#include "../Queue/GraphicsQueue.h"
#include "../SwapChain/VulkanSwapChain.h"

namespace ScrapEngine {

	class VulkanDevice
	{
	private:
		VkInstance instanceRef;
		VkSurfaceKHR VulkanSurfaceRef;

		VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

		GraphicsQueue::QueueFamilyIndices cached_indices;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; //physical graphics card
		VkDevice device; //logical connection to graphics card

		//List of Extensions to check
		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	public:
		VulkanDevice(VkInstance VulkanInstanceInputRef, VkSurfaceKHR VulkanSurfaceInputRef);

		//Turn off the logical device
		~VulkanDevice();

		//Choose and assign the best physicalDevice
		void choosePhysicalDevice();

		//Initialize the LogicalDevice
		void createLogicalDevice();

		//Return a reference to physicalDevice
		VkPhysicalDevice getPhysicalDevice() const;

		//Return a reference to logical device
		VkDevice getLogicalDevice() const;

		GraphicsQueue::QueueFamilyIndices getCachedQueueFamilyIndices() const;

		//Which queue families are supported by the device
		ScrapEngine::GraphicsQueue::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

		VulkanSwapChain::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		VkSampleCountFlagBits getMaxUsableSampleCount();

		VkSampleCountFlagBits getMsaaSamples() const;
	private:
		bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}

