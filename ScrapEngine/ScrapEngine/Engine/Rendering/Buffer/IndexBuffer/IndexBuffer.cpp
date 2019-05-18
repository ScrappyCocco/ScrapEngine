#include "IndexBuffer.h"
#include "Engine/Rendering/Memory/MemoryManager.h"
#include "Engine/Rendering/Buffer/BaseBuffer.h"
#include "Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h"

ScrapEngine::Render::IndexBuffer::IndexBuffer(const std::vector<uint32_t>* indices)
{
	const vk::DeviceSize buffer_size = sizeof((*indices)[0]) * indices->size();

	StagingBuffer* staging = new StagingBuffer(buffer_size, indices);

	BaseBuffer::create_buffer(buffer_size,
	                          vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer,
	                          vk::MemoryPropertyFlagBits::eDeviceLocal, index_buffer_, index_buffer_memory_);

	BaseBuffer::copy_buffer(staging->get_staging_buffer(), index_buffer_, buffer_size);

	delete staging;
}

ScrapEngine::Render::IndexBuffer::~IndexBuffer()
{
	VulkanDevice::static_logic_device_ref->destroyBuffer(index_buffer_);
	VulkanDevice::static_logic_device_ref->freeMemory(index_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::IndexBuffer::get_index_buffer()
{
	return &index_buffer_;
}
