#include "IndexBuffer.h"
#include "Engine/Rendering/Memory/MemoryManager.h"
#include "Engine/Rendering/Buffer/BaseBuffer.h"
#include "Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h"

ScrapEngine::IndexBuffer::IndexBuffer(const std::vector<uint32_t>* indices)
{
	vk::DeviceSize bufferSize = sizeof((*indices)[0]) * indices->size();

	StagingBuffer* Staging = new StagingBuffer(bufferSize, indices);
	
	BaseBuffer::createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, indexBuffer, indexBufferMemory);

	BaseBuffer::copyBuffer(Staging->getStagingBuffer(), indexBuffer, bufferSize);

	delete Staging;
}

ScrapEngine::IndexBuffer::~IndexBuffer()
{
	VulkanDevice::StaticLogicDeviceRef->destroyBuffer(indexBuffer);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(indexBufferMemory);
}

vk::Buffer* ScrapEngine::IndexBuffer::getIndexBuffer()
{
	return &indexBuffer;
}