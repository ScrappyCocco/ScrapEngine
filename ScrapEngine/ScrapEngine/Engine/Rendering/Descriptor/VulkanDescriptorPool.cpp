#include "VulkanDescriptorPool.h"
#include <array>

ScrapEngine::VulkanDescriptorPool::VulkanDescriptorPool(vk::Device* input_deviceRef, const std::vector<vk::Image>* swapChainImages)
	: deviceRef(input_deviceRef)
{
	std::array<vk::DescriptorPoolSize, 2> poolSizes = {
		vk::DescriptorPoolSize(vk::DescriptorType::eUniformBuffer, static_cast<uint32_t>(swapChainImages->size())),
		vk::DescriptorPoolSize(vk::DescriptorType::eCombinedImageSampler, static_cast<uint32_t>(swapChainImages->size())),
	
	};

	vk::DescriptorPoolCreateInfo poolInfo(
		vk::DescriptorPoolCreateFlags(), 
		static_cast<uint32_t>(swapChainImages->size()), 
		static_cast<uint32_t>(poolSizes.size()), poolSizes.data()
	);

	if (deviceRef->createDescriptorPool(&poolInfo, nullptr, &descriptorPool) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanDescriptorPool: Failed to create descriptor pool!");
	}
}

ScrapEngine::VulkanDescriptorPool::~VulkanDescriptorPool()
{
	deviceRef->destroyDescriptorPool(descriptorPool);
}

vk::DescriptorPool* ScrapEngine::VulkanDescriptorPool::getDescriptorPool()
{
	return &descriptorPool;
}
