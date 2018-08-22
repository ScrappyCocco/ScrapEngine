#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace ScrapEngine {

	class VulkanDepthResources
	{
	private:
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		VkDevice deviceRef;
	public:
		VulkanDepthResources(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDeviceRef, VkCommandPool CommandPool, VkQueue graphicsQueue, const VkExtent2D* swapChainExtent, VkSampleCountFlagBits msaaSamples);
		~VulkanDepthResources();

		static VkFormat findSupportedFormat(VkPhysicalDevice PhysicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		static VkFormat findDepthFormat(VkPhysicalDevice PhysicalDevice);
		static bool hasStencilComponent(VkFormat format);

		VkImage getDepthImage() const;
		VkDeviceMemory getDepthImageMemory() const;
		VkImageView getDepthImageView();

	};

}

