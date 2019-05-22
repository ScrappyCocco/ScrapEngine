#include <Engine/Rendering/Buffer/StagingBuffer/VertexStagingBuffer/VertexStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::VertexStagingBuffer::VertexStagingBuffer(const vk::DeviceSize& buffer_size,
                                                              const std::vector<Vertex>* vector_data)
{
	BaseBuffer::create_buffer(buffer_size, vk::BufferUsageFlagBits::eTransferSrc,
	                          vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::
	                          eHostCoherent, staging_buffer_, staging_buffer_memory_);
	void* data;
	VulkanDevice::get_instance()->get_logical_device()->mapMemory(staging_buffer_memory_, 0, buffer_size,
	                                                              vk::MemoryMapFlags(),
	                                                              &data);
	memcpy(data, vector_data->data(), static_cast<size_t>(buffer_size));
	VulkanDevice::get_instance()->get_logical_device()->unmapMemory(staging_buffer_memory_);
}
