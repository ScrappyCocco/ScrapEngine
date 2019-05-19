#include "VulkanCommandPool.h"

#include <stdexcept>
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::CommandPool* ScrapEngine::Render::VulkanCommandPool::static_command_pool_ref = nullptr;

//Class

ScrapEngine::Render::VulkanCommandPool::VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queue_family_indices)
{
	vk::CommandPoolCreateInfo pool_info(vk::CommandPoolCreateFlags(), queue_family_indices.graphics_family);

	if (VulkanDevice::static_logic_device_ref->createCommandPool(&pool_info, nullptr, &command_pool_) != vk::Result::
		eSuccess)
	{
		throw std::runtime_error("VulkanCommandPool: Failed to create command pool!");
	}

	static_command_pool_ref = &command_pool_;
}

ScrapEngine::Render::VulkanCommandPool::~VulkanCommandPool()
{
	VulkanDevice::static_logic_device_ref->destroyCommandPool(command_pool_);
}

vk::CommandPool* ScrapEngine::Render::VulkanCommandPool::get_command_pool()
{
	return &command_pool_;
}
