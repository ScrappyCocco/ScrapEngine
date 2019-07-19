#include <Engine/Rendering/Buffer/GenericBuffer/GenericBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>

ScrapEngine::Render::GenericBuffer::~GenericBuffer()
{
	destroy();
}

void ScrapEngine::Render::GenericBuffer::create_buffer(const vk::BufferCreateInfo& crate_info)
{
	BaseBuffer::create_buffer(crate_info.size, crate_info.usage, vk::MemoryPropertyFlagBits::eHostVisible,
	                          buffer_, buffer_memory_);
}

void ScrapEngine::Render::GenericBuffer::map(const vk::DeviceSize size, const vk::DeviceSize offset)
{
	VulkanDevice::get_instance()->get_logical_device()->mapMemory(buffer_memory_, offset, size,
	                                                              vk::MemoryMapFlags(), &mapped_memory_);
}

void ScrapEngine::Render::GenericBuffer::unmap()
{
	if (mapped_memory_)
	{
		VulkanDevice::get_instance()->get_logical_device()->unmapMemory(buffer_memory_);
		mapped_memory_ = nullptr;
	}
}

void ScrapEngine::Render::GenericBuffer::flush(const vk::DeviceSize size, const vk::DeviceSize offset) const
{
	vk::MappedMemoryRange mapped_range;
	mapped_range.setMemory(buffer_memory_);
	mapped_range.setOffset(offset);
	mapped_range.setSize(size);
	VulkanDevice::get_instance()->get_logical_device()->flushMappedMemoryRanges(1, &mapped_range);
}

void ScrapEngine::Render::GenericBuffer::bind(const vk::DeviceSize offset) const
{
	VulkanDevice::get_instance()->get_logical_device()->bindBufferMemory(buffer_, buffer_memory_, offset);
}

void ScrapEngine::Render::GenericBuffer::destroy() const
{
	VulkanDevice::get_instance()->get_logical_device()->destroyBuffer(buffer_);
	VulkanDevice::get_instance()->get_logical_device()->freeMemory(buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::GenericBuffer::get_buffer()
{
	return &buffer_;
}

void** ScrapEngine::Render::GenericBuffer::get_mapped_memory()
{
	return &mapped_memory_;
}
