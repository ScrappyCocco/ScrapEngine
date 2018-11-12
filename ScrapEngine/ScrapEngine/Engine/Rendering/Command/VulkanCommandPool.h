#pragma once

#include <vulkan/vulkan.hpp>
#include "../Queue/GraphicsQueue.h"

namespace ScrapEngine {

	class VulkanCommandPool
	{
	private:
		vk::CommandPool commandPool;
	public:
		static const vk::CommandPool* StaticCommandPoolRef;

		VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices);
		~VulkanCommandPool();

		vk::CommandPool* getCommandPool();
	};

}

