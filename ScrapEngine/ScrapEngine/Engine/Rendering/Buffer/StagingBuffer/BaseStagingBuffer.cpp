#include <Engine/Rendering/Buffer/StagingBuffer/BaseStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>


ScrapEngine::Render::BaseStagingBuffer::~BaseStagingBuffer()
{
	VulkanMemoryAllocator::get_instance()->destroy_buffer(staging_buffer_, staging_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::BaseStagingBuffer::get_staging_buffer()
{
	return &staging_buffer_;
}
