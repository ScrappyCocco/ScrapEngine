#include <Engine/Rendering/Buffer/StagingBuffer/BaseStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>


ScrapEngine::Render::BaseStagingBuffer::~BaseStagingBuffer()
{
	VulkanDevice::static_logic_device_ref->destroyBuffer(staging_buffer_);
	VulkanDevice::static_logic_device_ref->freeMemory(staging_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::BaseStagingBuffer::get_staging_buffer()
{
	return &staging_buffer_;
}

vk::DeviceMemory* ScrapEngine::Render::BaseStagingBuffer::get_staging_buffer_memory()
{
	return &staging_buffer_memory_;
}
