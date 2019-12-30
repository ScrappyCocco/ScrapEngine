#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Buffer/StagingBuffer/VertexStagingBuffer/VertexStagingBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::VertexBuffer::VertexBuffer(const std::vector<Vertex>* vertices)
{
	const vk::DeviceSize buffer_size(sizeof((*vertices)[0]) * vertices->size());

	//unique_ptr to be deleted after constructor
	std::unique_ptr<BaseStagingBuffer> staging = std::make_unique<VertexStagingBuffer>(buffer_size, vertices);

	vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		buffer_size,
		vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer,
		vk::SharingMode::eExclusive
	);

	VulkanMemoryAllocator::get_instance()->
		create_vertex_index_buffer(&buffer_info, vertex_buffer_, vertex_buffer_memory_);

	BaseBuffer::copy_buffer(staging->get_staging_buffer(), vertex_buffer_, buffer_size);
}

ScrapEngine::Render::VertexBuffer::~VertexBuffer()
{
	VulkanMemoryAllocator::get_instance()->destroy_buffer(vertex_buffer_, vertex_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::VertexBuffer::get_vertex_buffer()
{
	return &vertex_buffer_;
}
