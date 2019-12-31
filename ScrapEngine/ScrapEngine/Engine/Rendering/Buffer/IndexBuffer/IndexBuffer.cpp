#include <Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Buffer/StagingBuffer/IndicesStagingBuffer/IndicesStagingBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::IndexBuffer::IndexBuffer(const std::vector<uint32_t>* indices)
{
	const vk::DeviceSize buffer_size = sizeof((*indices)[0]) * indices->size();

	//unique_ptr to be deleted after constructor
	std::unique_ptr<BaseStagingBuffer> staging = std::make_unique<IndicesStagingBuffer>(buffer_size, indices);

	const vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		buffer_size,
		vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer,
		vk::SharingMode::eExclusive
	);

	VulkanMemoryAllocator::get_instance()->
		create_vertex_index_buffer(&buffer_info, index_buffer_, index_buffer_memory_);

	BaseBuffer::copy_buffer(staging->get_staging_buffer(), index_buffer_, buffer_size);
}

ScrapEngine::Render::IndexBuffer::~IndexBuffer()
{
	VulkanMemoryAllocator::get_instance()->destroy_buffer(index_buffer_, index_buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::IndexBuffer::get_index_buffer()
{
	return &index_buffer_;
}
