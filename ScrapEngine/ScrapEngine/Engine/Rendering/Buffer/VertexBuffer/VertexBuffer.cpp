#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Buffer/StagingBuffer/VertexStagingBuffer/VertexStagingBuffer.h>

ScrapEngine::Render::VertexBuffer::VertexBuffer(const std::vector<Vertex>* vertices)
{
	const vk::DeviceSize buffer_size(sizeof((*vertices)[0]) * vertices->size());

	//unique_ptr to be deleted after constructor
	std::unique_ptr<BaseStagingBuffer> staging = std::make_unique<VertexStagingBuffer>(buffer_size, vertices);

	BaseBuffer::create_buffer(buffer_size,
	                          vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer,
	                          vk::MemoryPropertyFlagBits::eDeviceLocal, vertex_buffer_, vertex_buffer_memory_);

	BaseBuffer::copy_buffer(staging->get_staging_buffer(), vertex_buffer_, buffer_size);
}

ScrapEngine::Render::VertexBuffer::~VertexBuffer()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyBuffer(vertex_buffer_);
	VulkanDevice::get_instance()->get_logical_device()->freeMemory(vertex_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::VertexBuffer::get_vertex_buffer()
{
	return &vertex_buffer_;
}
