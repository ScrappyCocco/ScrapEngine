#pragma once

#include <vulkan/vulkan.hpp>
#include "Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h"

namespace ScrapEngine {

	class BaseBuffer
	{
	public:
		static void createBuffer(const vk::DeviceSize& size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory);

		static void copyBuffer(vk::Buffer* srcBuffer, vk::Buffer& dstBuffer, const vk::DeviceSize& size);

		static vk::CommandBuffer* beginSingleTimeCommands();

		static void endSingleTimeCommands(vk::CommandBuffer* commandBuffer);
	};

}

