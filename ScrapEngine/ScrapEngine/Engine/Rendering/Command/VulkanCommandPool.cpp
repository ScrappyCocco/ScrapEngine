#include <Engine/Rendering/Command/VulkanCommandPool.h>

#include <stdexcept>
#include <Engine/Rendering/Device/VulkanDevice.h>

//Init static instance reference

ScrapEngine::Render::VulkanCommandPool* ScrapEngine::Render::VulkanCommandPool::instance_ = nullptr;

//Class

void ScrapEngine::Render::VulkanCommandPool::init(const BaseQueue::QueueFamilyIndices queue_family_indices)
{
	vk::CommandPoolCreateInfo pool_info(vk::CommandPoolCreateFlags(), queue_family_indices.graphics_family);

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

ScrapEngine::Render::VulkanCommandPool* ScrapEngine::Render::VulkanCommandPool::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanCommandPool();
	}
	return instance_;
}

vk::CommandPool* ScrapEngine::Render::VulkanCommandPool::get_command_pool()
{
	return &command_pool_;
}
