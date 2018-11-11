#pragma once

#include <vulkan/vulkan.hpp>
#include "../Queue/GraphicsQueue.h"

namespace ScrapEngine {

	class VulkanCommandPool
	{
	private:
		vk::CommandPool commandPool;

		vk::Device* deviceRef;
	public:
		static const vk::CommandPool* StaticCommandPoolRef;

		VulkanCommandPool(GraphicsQueue::QueueFamilyIndices queueFamilyIndices, vk::Device* input_deviceRef);
		~VulkanCommandPool();

		vk::CommandPool* getCommandPool();
	};

}

