#pragma once

#include <vulkan/vulkan.h>
#include "../Queue/GraphicsQueue.h"

namespace ScrapEngine {

	class VulkanCommandPool
	{
	private:
		VkCommandPool commandPool;

		VkDevice deviceRef;
	public:
		VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices, VkDevice input_deviceRef);
		~VulkanCommandPool();

		VkCommandPool getCommandPool() const;
	};

}

