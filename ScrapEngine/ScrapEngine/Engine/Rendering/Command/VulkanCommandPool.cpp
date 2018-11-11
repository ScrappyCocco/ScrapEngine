#include "VulkanCommandPool.h"

#include <stdexcept>

//Init Static Members

const vk::CommandPool* ScrapEngine::VulkanCommandPool::StaticCommandPoolRef = nullptr;

//Class

ScrapEngine::VulkanCommandPool::VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices, vk::Device* input_deviceRef)
	: deviceRef(input_deviceRef)
{
	vk::CommandPoolCreateInfo poolInfo(vk::CommandPoolCreateFlags(), queueFamilyIndices.graphicsFamily);

	if (deviceRef->createCommandPool(&poolInfo, nullptr, &commandPool) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanCommandPool: Failed to create command pool!");
	}

	StaticCommandPoolRef = &commandPool;
}

ScrapEngine::VulkanCommandPool::~VulkanCommandPool()
{
	deviceRef->destroyCommandPool(commandPool);
}

vk::CommandPool* ScrapEngine::VulkanCommandPool::getCommandPool()
{
	return &commandPool;
}
