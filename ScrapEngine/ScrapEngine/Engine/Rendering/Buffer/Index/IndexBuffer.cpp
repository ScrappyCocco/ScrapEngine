#include "IndexBuffer.h"

#include "../../Memory/MemoryManager.h"
#include "../BaseBuffer.h"
#include "../Staging/StagingBuffer.h"

#include <iostream>

ScrapEngine::IndexBuffer::IndexBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, const std::vector<uint32_t>* indices, VkCommandPool commandPool, VkQueue graphicsQueue)
	: deviceRef(input_deviceRef)
{
	VkDeviceSize bufferSize = sizeof((*indices)[0]) * indices->size();

	std::cout << "Test 1:" << sizeof((*indices)[0]) << std::endl;
	std::cout << "Test 2:" << sizeof(indices[0]) << std::endl;

	StagingBuffer* Staging = new StagingBuffer(deviceRef, PhysicalDevice, bufferSize, indices);

	BaseBuffer::createBuffer(deviceRef, PhysicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	BaseBuffer::copyBuffer(deviceRef, commandPool, graphicsQueue, Staging->getStagingBuffer(), indexBuffer, bufferSize);

	delete Staging;
}

ScrapEngine::IndexBuffer::~IndexBuffer()
{
	vkDestroyBuffer(deviceRef, indexBuffer, nullptr);
	vkFreeMemory(deviceRef, indexBufferMemory, nullptr);
}

VkBuffer ScrapEngine::IndexBuffer::getIndexBuffer() const
{
	return indexBuffer;
}
