#include "VulkanCommandPool.h"

#include <stdexcept>

ScrapEngine::VulkanCommandPool::VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices, VkDevice input_deviceRef) 
	: deviceRef(input_deviceRef)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
	poolInfo.flags = 0; // Optional

	if (vkCreateCommandPool(deviceRef, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
}


ScrapEngine::VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(deviceRef, commandPool, nullptr);
}

VkCommandPool ScrapEngine::VulkanCommandPool::getCommandPool() const
{
	return commandPool;
}
