#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::ImageStagingBuffer::ImageStagingBuffer(const vk::DeviceSize& image_size, stbi_uc* pixels)
{
	VulkanMemoryAllocator::get_instance()->create_transfer_staging_buffer(image_size, staging_buffer_, staging_buffer_memory_);
	
	void* data;
	VulkanMemoryAllocator::get_instance()->map_buffer_allocation(staging_buffer_memory_, &data);
	std::memcpy(data, pixels, static_cast<size_t>(image_size));
	VulkanMemoryAllocator::get_instance()->unmap_buffer_allocation(staging_buffer_memory_);
}

void ScrapEngine::Render::ImageStagingBuffer::copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
                                                                   const uint32_t width, const uint32_t height)
{
	vk::BufferImageCopy region(0, 0, 0, vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1),
	                           vk::Offset3D(), vk::Extent3D(width, height, 1));

	copy_buffer_to_image(buffer, image, &region, 1, vk::ImageLayout::eTransferDstOptimal);
}

void ScrapEngine::Render::ImageStagingBuffer::copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
                                                                   vk::BufferImageCopy* region, const int regioncount,
                                                                   const vk::ImageLayout layout)
{
	BaseBuffer::copy_buffer_to_image(buffer, image, region, regioncount, layout);
}
