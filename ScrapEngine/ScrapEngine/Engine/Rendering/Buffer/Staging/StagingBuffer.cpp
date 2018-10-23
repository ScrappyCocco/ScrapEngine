#include "StagingBuffer.h"
#include "../BaseBuffer.h"
#include "../../../Debug/DebugLog.h"

ScrapEngine::StagingBuffer::StagingBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::DeviceSize* imageSize, stbi_uc* pixels)
	: deviceRef(input_deviceRef)
{
	BaseBuffer::createBuffer(deviceRef, PhysicalDevice, imageSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);
	void* data;
	deviceRef->mapMemory(stagingBufferMemory, 0, *imageSize, vk::MemoryMapFlags(), &data);
	memcpy(data, pixels, static_cast<size_t>(*imageSize));
	deviceRef->unmapMemory(stagingBufferMemory);
}

ScrapEngine::StagingBuffer::~StagingBuffer()
{
	deviceRef->destroyBuffer(stagingBuffer);
	deviceRef->freeMemory(stagingBufferMemory);
}

void ScrapEngine::StagingBuffer::copyBufferToImage(vk::Device* input_deviceRef, vk::Buffer* buffer, vk::Image* image, uint32_t width, uint32_t height, vk::CommandPool* commandPool, vk::Queue* graphicsQueue)
{
	vk::CommandBuffer* commandBuffer = BaseBuffer::beginSingleTimeCommands(input_deviceRef, commandPool);

	vk::BufferImageCopy region(0, 0, 0, vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1), vk::Offset3D(), vk::Extent3D(width, height, 1));

	commandBuffer->copyBufferToImage(*buffer, *image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

	BaseBuffer::endSingleTimeCommands(input_deviceRef, commandBuffer, commandPool, graphicsQueue);
}

void ScrapEngine::StagingBuffer::copyBufferToImage(vk::Device* input_deviceRef, vk::Buffer* buffer, vk::Image* image, uint32_t width, uint32_t height, vk::CommandPool* commandPool, vk::Queue* graphicsQueue, vk::BufferImageCopy region, int regioncount, vk::ImageLayout layout)
{
	vk::CommandBuffer* commandBuffer = BaseBuffer::beginSingleTimeCommands(input_deviceRef, commandPool);

	commandBuffer->copyBufferToImage(*buffer, *image, layout, regioncount, &region);

	BaseBuffer::endSingleTimeCommands(input_deviceRef, commandBuffer, commandPool, graphicsQueue);
}

vk::Buffer* ScrapEngine::StagingBuffer::getStagingBuffer()
{
	return &stagingBuffer;
}

vk::DeviceMemory* ScrapEngine::StagingBuffer::getStagingBufferMemory()
{
	return &stagingBufferMemory;
}
