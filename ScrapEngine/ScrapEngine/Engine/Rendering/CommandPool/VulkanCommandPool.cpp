#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>
#include <stdexcept>
#include <Engine/Rendering/Device/VulkanDevice.h>
//Class

void ScrapEngine::Render::VulkanCommandPool::init(const BaseQueue::QueueFamilyIndices queue_family_indices,
                                                  const vk::CommandPoolCreateFlags& flags)
{
	vk::CommandPoolCreateInfo pool_info(flags, queue_family_indices.graphics_family);

	if (VulkanDevice::get_instance()->get_logical_device()->createCommandPool(&pool_info, nullptr, &command_pool_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("VulkanCommandPool: Failed to create command pool!");
	}
}

ScrapEngine::Render::VulkanCommandPool::~VulkanCommandPool()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyCommandPool(command_pool_);
}

vk::CommandPool* ScrapEngine::Render::VulkanCommandPool::get_command_pool()
{
	return &command_pool_;
}
