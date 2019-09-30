#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::ImageStagingBuffer::ImageStagingBuffer(const vk::DeviceSize& image_size, stbi_uc* pixels)
{
	BaseBuffer::create_buffer(image_size, vk::BufferUsageFlagBits::eTransferSrc,
	                          vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
	                          staging_buffer_, staging_buffer_memory_);
	void* data;
	VulkanDevice::get_instance()->get_logical_device()->
	                              mapMemory(staging_buffer_memory_, 0, image_size, vk::MemoryMapFlags(), &data);
	memcpy(data, pixels, static_cast<size_t>(image_size));
	VulkanDevice::get_instance()->get_logical_device()->unmapMemory(staging_buffer_memory_);
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
