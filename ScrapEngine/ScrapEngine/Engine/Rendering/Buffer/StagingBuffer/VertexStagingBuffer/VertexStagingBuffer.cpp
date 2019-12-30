#include <Engine/Rendering/Buffer/StagingBuffer/VertexStagingBuffer/VertexStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::VertexStagingBuffer::VertexStagingBuffer(const vk::DeviceSize& buffer_size,
                                                              const std::vector<Vertex>* vector_data)
{
	VulkanMemoryAllocator::get_instance()->create_transfer_staging_buffer(buffer_size, staging_buffer_, staging_buffer_memory_);
	
	void* data;
	VulkanMemoryAllocator::get_instance()->map_buffer_allocation(staging_buffer_memory_, &data);
	std::memcpy(data, vector_data->data(), static_cast<size_t>(buffer_size));
	VulkanMemoryAllocator::get_instance()->unmap_buffer_allocation(staging_buffer_memory_);
}
