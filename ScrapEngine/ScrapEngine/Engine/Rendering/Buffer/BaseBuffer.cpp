#include "BaseBuffer.h"

#include <stdexcept>
#include "../Memory/MemoryManager.h"

void ScrapEngine::BaseBuffer::createBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::DeviceSize* size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer & buffer, vk::DeviceMemory & bufferMemory)
{
	vk::BufferCreateInfo bufferInfo(
		vk::BufferCreateFlags(), 
		*size, 
		usage, 
		vk::SharingMode::eExclusive);

	if (input_deviceRef->createBuffer(&bufferInfo, nullptr, &buffer) != vk::Result::eSuccess) {
		throw std::runtime_error("BaseBuffer: Failed to create buffer!");
	}

	vk::MemoryRequirements memRequirements;
	input_deviceRef->getBufferMemoryRequirements(buffer, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(memRequirements.size, findMemoryType(memRequirements.memoryTypeBits, properties, PhysicalDevice));

	if (input_deviceRef->allocateMemory(&allocInfo, nullptr, &bufferMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	input_deviceRef->bindBufferMemory(buffer, bufferMemory, 0);
}

void ScrapEngine::BaseBuffer::copyBuffer(vk::Device* input_deviceRef, vk::CommandPool* commandPool, vk::Queue* graphicsQueue, vk::Buffer* srcBuffer, vk::Buffer& dstBuffer, vk::DeviceSize* size)
{
	vk::CommandBuffer* commandBuffer = beginSingleTimeCommands(input_deviceRef, commandPool);

	vk::BufferCopy copyRegion(0, 0, *size);

	commandBuffer->copyBuffer(*srcBuffer, dstBuffer, 1, &copyRegion);

	endSingleTimeCommands(input_deviceRef, commandBuffer, commandPool, graphicsQueue);
}

vk::CommandBuffer* ScrapEngine::BaseBuffer::beginSingleTimeCommands(vk::Device* deviceRef, vk::CommandPool* CommandPool)
{
	vk::CommandBufferAllocateInfo allocInfo(*CommandPool, vk::CommandBufferLevel::ePrimary, 1);

	vk::CommandBuffer* commandBuffer = new vk::CommandBuffer();
	deviceRef->allocateCommandBuffers(&allocInfo, commandBuffer);

	vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

	commandBuffer->begin(beginInfo);

	return commandBuffer;
}

void ScrapEngine::BaseBuffer::endSingleTimeCommands(vk::Device* deviceRef, vk::CommandBuffer* commandBuffer, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue)
{
	commandBuffer->end();

	vk::SubmitInfo submitInfo(0, nullptr, nullptr, 1, commandBuffer);
	graphicsQueue->submit(1, &submitInfo, nullptr);

	graphicsQueue->waitIdle();

	deviceRef->freeCommandBuffers(*CommandPool, 1, commandBuffer);
	delete commandBuffer;
}
