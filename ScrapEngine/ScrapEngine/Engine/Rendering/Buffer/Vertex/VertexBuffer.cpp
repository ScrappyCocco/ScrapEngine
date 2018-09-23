#include "VertexBuffer.h"

#include "../../Memory/MemoryManager.h"
#include "../BaseBuffer.h"
#include "../Staging/StagingBuffer.h"

ScrapEngine::VertexBuffer::VertexBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<ScrapEngine::Vertex>* vertices, vk::CommandPool* commandPool, vk::Queue* graphicsQueue)
	: deviceRef(input_deviceRef)
{
	vk::DeviceSize bufferSize(sizeof((*vertices)[0]) * vertices->size());

	StagingBuffer* Staging = new StagingBuffer(deviceRef, PhysicalDevice, &bufferSize, vertices);

	BaseBuffer::createBuffer(deviceRef, PhysicalDevice, &bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, vertexBuffer, vertexBufferMemory);

	BaseBuffer::copyBuffer(deviceRef, commandPool, graphicsQueue, Staging->getStagingBuffer(), vertexBuffer, &bufferSize);

	delete Staging;
}

ScrapEngine::VertexBuffer::~VertexBuffer()
{
	deviceRef->destroyBuffer(vertexBuffer);
	deviceRef->freeMemory(vertexBufferMemory);
}

vk::Buffer* ScrapEngine::VertexBuffer::getVertexBuffer()
{
	return &vertexBuffer;
}
