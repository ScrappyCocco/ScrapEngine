#include "VulkanDescriptorPool.h"
#include <array>

ScrapEngine::VulkanDescriptorPool::VulkanDescriptorPool(VkDevice input_deviceRef, const std::vector<VkImage>* swapChainImages) 
	: deviceRef(input_deviceRef)
{
	std::array<VkDescriptorPoolSize, 2> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages->size());
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages->size());

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(swapChainImages->size());

	if (vkCreateDescriptorPool(deviceRef, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

ScrapEngine::VulkanDescriptorPool::~VulkanDescriptorPool()
{
	vkDestroyDescriptorPool(deviceRef, descriptorPool, nullptr);
}

VkDescriptorPool ScrapEngine::VulkanDescriptorPool::getDescriptorPool() const
{
	return descriptorPool;
}
