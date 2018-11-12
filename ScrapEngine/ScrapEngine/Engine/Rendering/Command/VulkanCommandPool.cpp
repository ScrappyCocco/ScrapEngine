#include "VulkanCommandPool.h"

#include <stdexcept>
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::CommandPool* ScrapEngine::VulkanCommandPool::StaticCommandPoolRef = nullptr;

//Class

ScrapEngine::VulkanCommandPool::VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices)
{
	vk::CommandPoolCreateInfo poolInfo(vk::CommandPoolCreateFlags(), queueFamilyIndices.graphicsFamily);

	if (VulkanDevice::StaticLogicDeviceRef->createCommandPool(&poolInfo, nullptr, &commandPool) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanCommandPool: Failed to create command pool!");
	}

	StaticCommandPoolRef = &commandPool;
}

ScrapEngine::VulkanCommandPool::~VulkanCommandPool()
{
	VulkanDevice::StaticLogicDeviceRef->destroyCommandPool(commandPool);
}

vk::CommandPool* ScrapEngine::VulkanCommandPool::getCommandPool()
{
	return &commandPool;
}
