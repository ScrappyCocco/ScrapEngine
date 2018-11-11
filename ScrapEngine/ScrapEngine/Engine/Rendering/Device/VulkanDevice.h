#pragma once

#include <vulkan/vulkan.hpp>
#include "../Instance/VukanInstance.h"
#include "../Window/VulkanSurface.h"
#include "../../Debug/DebugLog.h"
#include "../Queue/GraphicsQueue.h"
#include "../SwapChain/VulkanSwapChain.h"

namespace ScrapEngine {

	class VulkanDevice
	{
	private:
		vk::Instance* instanceRef;
		vk::SurfaceKHR* VulkanSurfaceRef;

		vk::SampleCountFlagBits msaaSamples = vk::SampleCountFlagBits::e1;

		GraphicsQueue::QueueFamilyIndices cached_indices;

		vk::PhysicalDevice physicalDevice; //physical graphics card
		vk::Device device; //logical connection to graphics card

		//List of Extensions to check
		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	public:
		static const vk::Device* StaticLogicDeviceRef;
		static const vk::PhysicalDevice* StaticPhysicalDeviceRef;

		VulkanDevice(vk::Instance* VulkanInstanceInputRef, vk::SurfaceKHR* VulkanSurfaceInputRef);

		//Turn off the logical device
		~VulkanDevice();

		//Choose and assign the best physicalDevice
		void choosePhysicalDevice();

		//Initialize the LogicalDevice
		void createLogicalDevice();

		//Return a reference to physicalDevice
		vk::PhysicalDevice* getPhysicalDevice();

		//Return a reference to logical device
		vk::Device* getLogicalDevice();

		GraphicsQueue::QueueFamilyIndices getCachedQueueFamilyIndices() const;

		//Which queue families are supported by the device
		ScrapEngine::GraphicsQueue::QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice* device, vk::SurfaceKHR* surface);

		VulkanSwapChain::SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice* device);

		vk::SampleCountFlagBits getMaxUsableSampleCount();

		vk::SampleCountFlagBits getMsaaSamples() const;
	private:
		bool isDeviceSuitable(vk::PhysicalDevice* device, vk::SurfaceKHR* surface);

		bool checkDeviceExtensionSupport(vk::PhysicalDevice* device);
	};
}

