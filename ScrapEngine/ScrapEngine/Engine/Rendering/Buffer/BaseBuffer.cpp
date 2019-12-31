#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/CommandPool/Singleton/SingletonCommandPool.h>
#include <Engine/Rendering/Queue/GraphicsQueue/GraphicsQueue.h>

void ScrapEngine::Render::BaseBuffer::copy_buffer(vk::Buffer* src_buffer, vk::Buffer& dst_buffer,
                                                  const vk::DeviceSize& size, const vk::DeviceSize& scr_offset,
                                                  const vk::DeviceSize& dst_offset,
                                                  const uint32_t region_count)
{
	const std::unique_ptr<vk::CommandBuffer> command_buffer = begin_single_time_command();

	vk::BufferCopy copy_region(scr_offset, dst_offset, size);

	command_buffer->copyBuffer(*src_buffer, dst_buffer, region_count, &copy_region);

	end_and_submit_single_time_command(command_buffer);
}

void ScrapEngine::Render::BaseBuffer::copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
                                                           vk::BufferImageCopy* region,
                                                           const int regioncount, const vk::ImageLayout layout)
{
	const std::unique_ptr<vk::CommandBuffer> command_buffer = begin_single_time_command();

	command_buffer->copyBufferToImage(*buffer, *image, layout, regioncount, region);

	end_and_submit_single_time_command(command_buffer);
}

std::unique_ptr<vk::CommandBuffer> ScrapEngine::Render::BaseBuffer::begin_single_time_command()
{
	vk::CommandBufferAllocateInfo alloc_info(*SingletonCommandPool::get_instance(),
	                                         vk::CommandBufferLevel::ePrimary,
	                                         1);

	vk::CommandBuffer* command_buffer = new vk::CommandBuffer();
	VulkanDevice::get_instance()->get_logical_device()->allocateCommandBuffers(&alloc_info, command_buffer);

	const vk::CommandBufferBeginInfo begin_info(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

	command_buffer->begin(begin_info);

	return std::unique_ptr<vk::CommandBuffer>(command_buffer);
}

void ScrapEngine::Render::BaseBuffer::end_and_submit_single_time_command(
	const std::unique_ptr<vk::CommandBuffer>& command_buffer)
{
	command_buffer->end();

	vk::SubmitInfo submit_info(0, nullptr, nullptr, 1, command_buffer.get());
	GraphicsQueue::get_instance()->get_queue()->submit(1, &submit_info, nullptr);

	GraphicsQueue::get_instance()->get_queue()->waitIdle();

	VulkanDevice::get_instance()->get_logical_device()->freeCommandBuffers(
		*SingletonCommandPool::get_instance(),
		1, command_buffer.get());
}
