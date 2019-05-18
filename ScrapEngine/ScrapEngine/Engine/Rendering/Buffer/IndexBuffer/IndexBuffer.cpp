#include "IndexBuffer.h"
#include "Engine/Rendering/Memory/MemoryManager.h"
#include "Engine/Rendering/Buffer/BaseBuffer.h"
#include "Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h"

ScrapEngine::Render::IndexBuffer::IndexBuffer(const std::vector<uint32_t>* indices)
{
	const vk::DeviceSize buffer_size = sizeof((*indices)[0]) * indices->size();

	StagingBuffer* staging = new StagingBuffer(buffer_size, indices);
	
	BaseBuffer::create_buffer(buffer_size, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, indexBuffer, indexBufferMemory);

	BaseBuffer::copy_buffer(staging->getStagingBuffer(), indexBuffer, buffer_size);

	delete staging;
}

ScrapEngine::Render::IndexBuffer::~IndexBuffer()
{
	VulkanDevice::StaticLogicDeviceRef->destroyBuffer(indexBuffer);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(indexBufferMemory);
}

vk::Buffer* ScrapEngine::Render::IndexBuffer::getIndexBuffer()
{
	return &indexBuffer;
}
