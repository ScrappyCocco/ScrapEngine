#include "StagingBuffer.h"
#include "../BaseBuffer.h"
#include "../../../Debug/DebugLog.h"

ScrapEngine::StagingBuffer::StagingBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, VkDeviceSize imageSize, stbi_uc* pixels)
	: deviceRef(input_deviceRef)
{
	BaseBuffer::createBuffer(deviceRef, PhysicalDevice, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
	void* data;
	vkMapMemory(deviceRef, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(deviceRef, stagingBufferMemory);
}

ScrapEngine::StagingBuffer::~StagingBuffer()
{
	vkDestroyBuffer(deviceRef, stagingBuffer, nullptr);
	vkFreeMemory(deviceRef, stagingBufferMemory, nullptr);
}

void ScrapEngine::StagingBuffer::copyBufferToImage(VkDevice input_deviceRef, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	VkCommandBuffer commandBuffer = BaseBuffer::beginSingleTimeCommands(input_deviceRef, commandPool);

	VkBufferImageCopy region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		width,
		height,
		1
	};

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	BaseBuffer::endSingleTimeCommands(input_deviceRef, commandBuffer, commandPool, graphicsQueue);
}

VkBuffer ScrapEngine::StagingBuffer::getStagingBuffer() const
{
	return stagingBuffer;
}

VkDeviceMemory ScrapEngine::StagingBuffer::getStagingBufferMemory() const
{
	return stagingBufferMemory;
}
