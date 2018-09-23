#include "IndexBuffer.h"

#include "../../Memory/MemoryManager.h"
#include "../BaseBuffer.h"
#include "../Staging/StagingBuffer.h"

#include <iostream>

ScrapEngine::IndexBuffer::IndexBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<uint32_t>* indices, vk::CommandPool* commandPool, vk::Queue* graphicsQueue)
	: deviceRef(input_deviceRef)
{
	vk::DeviceSize bufferSize = sizeof((*indices)[0]) * indices->size();

	StagingBuffer* Staging = new StagingBuffer(deviceRef, PhysicalDevice, &bufferSize, indices);
	
	BaseBuffer::createBuffer(deviceRef, PhysicalDevice, &bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, indexBuffer, indexBufferMemory);

	BaseBuffer::copyBuffer(deviceRef, commandPool, graphicsQueue, Staging->getStagingBuffer(), indexBuffer, &bufferSize);

	delete Staging;
}

ScrapEngine::IndexBuffer::~IndexBuffer()
{
	deviceRef->destroyBuffer(indexBuffer);
	deviceRef->freeMemory(indexBufferMemory);
}

vk::Buffer* ScrapEngine::IndexBuffer::getIndexBuffer()
{
	return &indexBuffer;
}
