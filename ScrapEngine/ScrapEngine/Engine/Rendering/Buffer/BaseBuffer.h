#pragma once

#include <vulkan/vulkan.h>
#include "VulkanCommandBuffer.h"

namespace ScrapEngine {

	class BaseBuffer
	{
	public:
		static void createBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

		static void copyBuffer(VkDevice input_deviceRef, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	
		static VkCommandBuffer beginSingleTimeCommands(VkDevice deviceRef, VkCommandPool CommandPool);

		static void endSingleTimeCommands(VkDevice deviceRef, VkCommandBuffer commandBuffer, VkCommandPool CommandPool, VkQueue graphicsQueue);
	};

}

