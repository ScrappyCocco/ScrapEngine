#include "VertexBuffer.h"

#include "Engine/Rendering/Buffer/BaseBuffer.h"
#include "Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h"

ScrapEngine::VertexBuffer::VertexBuffer(const std::vector<ScrapEngine::Vertex>* vertices)
{
	vk::DeviceSize bufferSize(sizeof((*vertices)[0]) * vertices->size());

	StagingBuffer* Staging = new StagingBuffer(bufferSize, vertices);

	BaseBuffer::createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, vertexBuffer, vertexBufferMemory);

	BaseBuffer::copyBuffer(Staging->getStagingBuffer(), vertexBuffer, bufferSize);

	delete Staging;
}

ScrapEngine::VertexBuffer::~VertexBuffer()
{
	VulkanDevice::StaticLogicDeviceRef->destroyBuffer(vertexBuffer);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(vertexBufferMemory);
}

vk::Buffer* ScrapEngine::VertexBuffer::getVertexBuffer()
{
	return &vertexBuffer;
}
