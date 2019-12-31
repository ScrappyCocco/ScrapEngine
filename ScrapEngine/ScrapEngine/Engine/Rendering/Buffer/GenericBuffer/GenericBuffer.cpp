#include <Engine/Rendering/Buffer/GenericBuffer/GenericBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::GenericBuffer::~GenericBuffer()
{
	destroy();
}

void ScrapEngine::Render::GenericBuffer::create_buffer(const vk::BufferCreateInfo& crate_info)
{
	const vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		crate_info.size,
		crate_info.usage,
		vk::SharingMode::eExclusive
	);

	VmaAllocationCreateInfo alloc_info = {};
	alloc_info.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
	alloc_info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
	alloc_info.flags = VMA_ALLOCATION_CREATE_DONT_BIND_BIT;

	VulkanMemoryAllocator::get_instance()->
		create_generic_buffer(&buffer_info, &alloc_info, buffer_, buffer_memory_);

	setup_descriptor();

	bind();
}

void ScrapEngine::Render::GenericBuffer::setup_descriptor(const vk::DeviceSize size, const vk::DeviceSize offset)
{
	descriptor_.setOffset(offset);
	descriptor_.setBuffer(buffer_);
	descriptor_.setRange(size);
}

void ScrapEngine::Render::GenericBuffer::map(const vk::DeviceSize size, const vk::DeviceSize offset)
{
	VulkanMemoryAllocator::get_instance()->map_buffer_allocation(buffer_memory_, &mapped_memory_);
}

void ScrapEngine::Render::GenericBuffer::unmap()
{
	if (mapped_memory_)
	{
		VulkanMemoryAllocator::get_instance()->unmap_buffer_allocation(buffer_memory_);
		mapped_memory_ = nullptr;
	}
}

void ScrapEngine::Render::GenericBuffer::flush(const vk::DeviceSize size, const vk::DeviceSize offset)
{
	VulkanMemoryAllocator::get_instance()->flush_buffer_allocation(buffer_memory_, size, offset);
}

void ScrapEngine::Render::GenericBuffer::bind(const vk::DeviceSize offset)
{
	VulkanMemoryAllocator::get_instance()->bind_buffer(buffer_, buffer_memory_, offset);
}

void ScrapEngine::Render::GenericBuffer::destroy()
{
	//Check if unmap is necessary
	unmap();
	//Destroy the buffer and its memory
	VulkanMemoryAllocator::get_instance()->destroy_buffer(buffer_, buffer_memory_);
}

vk::Buffer* ScrapEngine::Render::GenericBuffer::get_buffer()
{
	return &buffer_;
}

void* ScrapEngine::Render::GenericBuffer::get_mapped_memory() const
{
	return mapped_memory_;
}
