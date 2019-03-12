#include "StagingBuffer.h"
#include "../BaseBuffer.h"

ScrapEngine::StagingBuffer::StagingBuffer(const vk::DeviceSize& imageSize, stbi_uc* pixels)
{
	BaseBuffer::createBuffer(imageSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);
	void* data;
	VulkanDevice::StaticLogicDeviceRef->mapMemory(stagingBufferMemory, 0, imageSize, vk::MemoryMapFlags(), &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	VulkanDevice::StaticLogicDeviceRef->unmapMemory(stagingBufferMemory);
}

ScrapEngine::StagingBuffer::~StagingBuffer()
{
	VulkanDevice::StaticLogicDeviceRef->destroyBuffer(stagingBuffer);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(stagingBufferMemory);
}

void ScrapEngine::StagingBuffer::copyBufferToImage(vk::Buffer* buffer, vk::Image* image, const uint32_t& width, const uint32_t& height)
{
	vk::CommandBuffer* commandBuffer = BaseBuffer::beginSingleTimeCommands();

	vk::BufferImageCopy region(0, 0, 0, vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1), vk::Offset3D(), vk::Extent3D(width, height, 1));

	commandBuffer->copyBufferToImage(*buffer, *image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

	BaseBuffer::endSingleTimeCommands(commandBuffer);
}

void ScrapEngine::StagingBuffer::copyBufferToImage(vk::Buffer* buffer, vk::Image* image, const uint32_t& width, const uint32_t& height, vk::BufferImageCopy* region, int regioncount, vk::ImageLayout layout)
{
	vk::CommandBuffer* commandBuffer = BaseBuffer::beginSingleTimeCommands();

	commandBuffer->copyBufferToImage(*buffer, *image, layout, regioncount, region);

	BaseBuffer::endSingleTimeCommands(commandBuffer);
}

vk::Buffer* ScrapEngine::StagingBuffer::getStagingBuffer()
{
	return &stagingBuffer;
}

vk::DeviceMemory* ScrapEngine::StagingBuffer::getStagingBufferMemory()
{
	return &stagingBufferMemory;
}
