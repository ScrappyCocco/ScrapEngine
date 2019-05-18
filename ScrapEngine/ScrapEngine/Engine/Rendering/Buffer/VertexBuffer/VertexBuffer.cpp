#include "VertexBuffer.h"

#include "Engine/Rendering/Buffer/BaseBuffer.h"
#include "Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h"

ScrapEngine::Render::VertexBuffer::VertexBuffer(const std::vector<ScrapEngine::Vertex>* vertices)
{
	vk::DeviceSize bufferSize(sizeof((*vertices)[0]) * vertices->size());

	ScrapEngine::Render::StagingBuffer* Staging = new StagingBuffer(bufferSize, vertices);

	BaseBuffer::create_buffer(bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, vertexBuffer, vertexBufferMemory);

	BaseBuffer::copy_buffer(Staging->getStagingBuffer(), vertexBuffer, bufferSize);

	delete Staging;
}

ScrapEngine::Render::VertexBuffer::~VertexBuffer()
{
	VulkanDevice::StaticLogicDeviceRef->destroyBuffer(vertexBuffer);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(vertexBufferMemory);
}

vk::Buffer* ScrapEngine::Render::VertexBuffer::getVertexBuffer()
{
	return &vertexBuffer;
}
