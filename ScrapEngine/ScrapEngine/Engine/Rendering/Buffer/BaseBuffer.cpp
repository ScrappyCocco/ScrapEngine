#include "BaseBuffer.h"

#include <stdexcept>
#include "../Memory/MemoryManager.h"
#include "../Base/StaticTypes.h"

void ScrapEngine::BaseBuffer::createBuffer(const vk::DeviceSize& size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory)
{
	vk::BufferCreateInfo bufferInfo(
		vk::BufferCreateFlags(), 
		size, 
		usage, 
		vk::SharingMode::eExclusive
	);

	if (VulkanDevice::StaticLogicDeviceRef->createBuffer(&bufferInfo, nullptr, &buffer) != vk::Result::eSuccess) {
		throw std::runtime_error("BaseBuffer: Failed to create buffer!");
	}

	vk::MemoryRequirements memRequirements;
	VulkanDevice::StaticLogicDeviceRef->getBufferMemoryRequirements(buffer, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(memRequirements.size, findMemoryType(memRequirements.memoryTypeBits, properties));

	if (VulkanDevice::StaticLogicDeviceRef->allocateMemory(&allocInfo, nullptr, &bufferMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("BaseBuffer: Failed to allocate buffer memory!");
	}

	VulkanDevice::StaticLogicDeviceRef->bindBufferMemory(buffer, bufferMemory, 0);
}

void ScrapEngine::BaseBuffer::copyBuffer(vk::Buffer* srcBuffer, vk::Buffer& dstBuffer, const vk::DeviceSize& size)
{
	vk::CommandBuffer* commandBuffer = beginSingleTimeCommands();

	vk::BufferCopy copyRegion(0, 0, size);

	commandBuffer->copyBuffer(*srcBuffer, dstBuffer, 1, &copyRegion);

	endSingleTimeCommands(commandBuffer);
}

vk::CommandBuffer* ScrapEngine::BaseBuffer::beginSingleTimeCommands()
{
	vk::CommandBufferAllocateInfo allocInfo(*VulkanCommandPool::StaticCommandPoolRef, vk::CommandBufferLevel::ePrimary, 1);

	vk::CommandBuffer* commandBuffer = new vk::CommandBuffer();
	VulkanDevice::StaticLogicDeviceRef->allocateCommandBuffers(&allocInfo, commandBuffer);

	vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

	commandBuffer->begin(beginInfo);

	return commandBuffer;
}

void ScrapEngine::BaseBuffer::endSingleTimeCommands(vk::CommandBuffer* commandBuffer)
{
	commandBuffer->end();

	vk::SubmitInfo submitInfo(0, nullptr, nullptr, 1, commandBuffer);
	GraphicsQueue::StaticGraphicsQueueRef->submit(1, &submitInfo, nullptr);

	GraphicsQueue::StaticGraphicsQueueRef->waitIdle();

	VulkanDevice::StaticLogicDeviceRef->freeCommandBuffers(*VulkanCommandPool::StaticCommandPoolRef, 1, commandBuffer);
	delete commandBuffer;
}
