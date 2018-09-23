#pragma once

#include <vulkan/vulkan.hpp>
#include "VulkanCommandBuffer.h"

namespace ScrapEngine {

	class BaseBuffer
	{
	public:
		static void createBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::DeviceSize* size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory);

		static void copyBuffer(vk::Device* input_deviceRef, vk::CommandPool* commandPool, vk::Queue* graphicsQueue, vk::Buffer* srcBuffer, vk::Buffer& dstBuffer, vk::DeviceSize* size);

		static vk::CommandBuffer* beginSingleTimeCommands(vk::Device* deviceRef, vk::CommandPool* CommandPool);

		static void endSingleTimeCommands(vk::Device* deviceRef, vk::CommandBuffer* commandBuffer, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue);
	};

}

