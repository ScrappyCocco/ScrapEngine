#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::ImageStagingBuffer::ImageStagingBuffer(const vk::DeviceSize& image_size, stbi_uc* pixels)
{
	BaseBuffer::create_buffer(image_size, vk::BufferUsageFlagBits::eTransferSrc,
	                          vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
	                          staging_buffer_, staging_buffer_memory_);
	void* data;
	VulkanDevice::static_logic_device_ref->
		mapMemory(staging_buffer_memory_, 0, image_size, vk::MemoryMapFlags(), &data);
	memcpy(data, pixels, static_cast<size_t>(image_size));
	VulkanDevice::static_logic_device_ref->unmapMemory(staging_buffer_memory_);
}

void ScrapEngine::Render::ImageStagingBuffer::copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
                                                                   const uint32_t& width, const uint32_t& height)
{
	vk::CommandBuffer* command_buffer = BaseBuffer::begin_single_time_commands();

	vk::BufferImageCopy region(0, 0, 0, vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1),
	                           vk::Offset3D(), vk::Extent3D(width, height, 1));

	command_buffer->copyBufferToImage(*buffer, *image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

	BaseBuffer::end_single_time_commands(command_buffer);
}

void ScrapEngine::Render::ImageStagingBuffer::copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
                                                                   const uint32_t& width, const uint32_t& height,
                                                                   vk::BufferImageCopy* region, int regioncount,
                                                                   vk::ImageLayout layout)
{
	vk::CommandBuffer* command_buffer = BaseBuffer::begin_single_time_commands();

	command_buffer->copyBufferToImage(*buffer, *image, layout, regioncount, region);

	BaseBuffer::end_single_time_commands(command_buffer);
}
