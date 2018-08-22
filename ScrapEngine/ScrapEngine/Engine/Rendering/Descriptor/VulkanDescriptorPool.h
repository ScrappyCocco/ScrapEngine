#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace ScrapEngine {

	class VulkanDescriptorPool
	{
	private:
		VkDescriptorPool descriptorPool;

		VkDevice deviceRef;
	public:
		VulkanDescriptorPool(VkDevice input_deviceRef, const std::vector<VkImage>* swapChainImages);
		~VulkanDescriptorPool();

		VkDescriptorPool getDescriptorPool() const;
	};

}

