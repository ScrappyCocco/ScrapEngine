#pragma once

#include <vulkan/vulkan.h>
#include "../SwapChain/VulkanSwapChain.h"

namespace ScrapEngine{

	class VulkanColorResources
	{
	private:
		VkImage colorImage;
		VkDeviceMemory colorImageMemory;
		VkImageView colorImageView;

		VkDevice deviceRef;
	public:
		VulkanColorResources(VkDevice input_deviceRef, VkPhysicalDevice input_PhysicalDeviceRef, VkCommandPool CommandPool, VkQueue graphicsQueue, VkSampleCountFlagBits msaaSamples, ScrapEngine::VulkanSwapChain* swapChainRef);
		~VulkanColorResources();

		VkImage getColorImage() const;
		VkImageView getColorImageView() const;
	};

}
