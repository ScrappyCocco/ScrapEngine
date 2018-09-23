#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine {

	class VulkanDescriptorPool
	{
	private:
		vk::DescriptorPool descriptorPool;

		vk::Device* deviceRef;
	public:
		VulkanDescriptorPool(vk::Device* input_deviceRef, const std::vector<vk::Image>* swapChainImages);
		~VulkanDescriptorPool();

		vk::DescriptorPool* getDescriptorPool();
	};

}

