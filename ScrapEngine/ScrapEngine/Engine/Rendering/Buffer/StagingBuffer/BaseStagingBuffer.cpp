#include <Engine/Rendering/Buffer/StagingBuffer/BaseStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>


ScrapEngine::Render::BaseStagingBuffer::~BaseStagingBuffer()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyBuffer(staging_buffer_);
	VulkanDevice::get_instance()->get_logical_device()->freeMemory(staging_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::BaseStagingBuffer::get_staging_buffer()
{
	return &staging_buffer_;
}

vk::DeviceMemory* ScrapEngine::Render::BaseStagingBuffer::get_staging_buffer_memory()
{
	return &staging_buffer_memory_;
}
