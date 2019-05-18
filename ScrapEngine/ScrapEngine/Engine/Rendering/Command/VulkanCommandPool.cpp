#include "VulkanCommandPool.h"

#include <stdexcept>
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::CommandPool* ScrapEngine::Render::VulkanCommandPool::StaticCommandPoolRef = nullptr;

//Class

ScrapEngine::Render::VulkanCommandPool::VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices)
{
	vk::CommandPoolCreateInfo poolInfo(vk::CommandPoolCreateFlags(), queueFamilyIndices.graphicsFamily);

	if (VulkanDevice::StaticLogicDeviceRef->createCommandPool(&poolInfo, nullptr, &commandPool) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanCommandPool: Failed to create command pool!");
	}

	StaticCommandPoolRef = &commandPool;
}

ScrapEngine::Render::VulkanCommandPool::~VulkanCommandPool()
{
	VulkanDevice::StaticLogicDeviceRef->destroyCommandPool(commandPool);
}

vk::CommandPool* ScrapEngine::Render::VulkanCommandPool::getCommandPool()
{
	return &commandPool;
}
