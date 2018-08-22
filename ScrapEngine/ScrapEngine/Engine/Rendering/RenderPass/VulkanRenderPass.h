#pragma once

#include <vulkan/vulkan.h>

namespace ScrapEngine {

	class VulkanRenderPass
	{
	private:
		VkRenderPass renderPass;

		VkDevice deviceRef;
	public:
		VulkanRenderPass(VkDevice input_deviceRef, VkFormat swapChainImageFormat, VkPhysicalDevice PhysicalDeviceRef, VkSampleCountFlagBits msaaSamples);
		~VulkanRenderPass();

		VkRenderPass getRenderPass() const;
	};

}

