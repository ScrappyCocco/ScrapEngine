#pragma once

#include <vulkan/vulkan.hpp>
#include "../SwapChain/VulkanSwapChain.h"

namespace ScrapEngine{

	class VulkanColorResources
	{
	private:
		vk::Image colorImage;
		vk::DeviceMemory colorImageMemory;
		vk::ImageView colorImageView;

		vk::Device* deviceRef;
	public:
		VulkanColorResources(vk::Device* input_deviceRef, vk::PhysicalDevice* input_PhysicalDeviceRef, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, vk::SampleCountFlagBits msaaSamples, ScrapEngine::VulkanSwapChain* swapChainRef);
		~VulkanColorResources();

		vk::Image* getColorImage();
		vk::ImageView* getColorImageView();
	};

}
