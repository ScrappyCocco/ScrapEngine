#include <Engine/Rendering/Buffer/BaseBuffer.h>

#include <stdexcept>
#include <Engine/Rendering/Memory/MemoryManager.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/CommandPool/Singleton/SingletonCommandPool.h>
#include <Engine/Rendering/Queue/GraphicsQueue/GraphicsQueue.h>

void ScrapEngine::Render::BaseBuffer::create_buffer(const vk::DeviceSize& size, const vk::BufferUsageFlags& usage,
                                                    const vk::MemoryPropertyFlags& properties, vk::Buffer& buffer,
                                                    vk::DeviceMemory& buffer_memory, const bool auto_bind_memory)
{
	const vk::Device* device = VulkanDevice::get_instance()->get_logical_device();

	vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		size,
		usage,
		vk::SharingMode::eExclusive
	);

	if (device->createBuffer(&buffer_info, nullptr, &buffer)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("BaseBuffer: Failed to create buffer!");
	}

	vk::MemoryRequirements mem_requirements;
	device->getBufferMemoryRequirements(buffer, &mem_requirements);

	vk::MemoryAllocateInfo alloc_info(mem_requirements.size,
	                                  find_memory_type(mem_requirements.memoryTypeBits, properties));

	if (device->allocateMemory(&alloc_info, nullptr, &buffer_memory)
		!= vk::Result::eSuccess
	)
	{
		throw std::runtime_error("BaseBuffer: Failed to allocate buffer memory!");
	}

	if (auto_bind_memory) { //bind memory
		device->bindBufferMemory(buffer, buffer_memory, 0);
	}
}

void ScrapEngine::Render::BaseBuffer::copy_buffer(vk::Buffer* src_buffer, vk::Buffer& dst_buffer,
                                                  const vk::DeviceSize& size)
{
	vk::CommandBuffer* command_buffer = begin_single_time_commands();

	vk::BufferCopy copy_region(0, 0, size);

	command_buffer->copyBuffer(*src_buffer, dst_buffer, 1, &copy_region);

	end_single_time_commands(command_buffer);
}

vk::CommandBuffer* ScrapEngine::Render::BaseBuffer::begin_single_time_commands()
{
	vk::CommandBufferAllocateInfo alloc_info(*SingletonCommandPool::get_instance()->get_command_pool(),
	                                         vk::CommandBufferLevel::ePrimary,
	                                         1);

	vk::CommandBuffer* command_buffer = new vk::CommandBuffer();
	VulkanDevice::get_instance()->get_logical_device()->allocateCommandBuffers(&alloc_info, command_buffer);

	const vk::CommandBufferBeginInfo begin_info(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

	command_buffer->begin(begin_info);

	return command_buffer;
}

void ScrapEngine::Render::BaseBuffer::end_single_time_commands(vk::CommandBuffer* command_buffer)
{
	command_buffer->end();

	vk::SubmitInfo submit_info(0, nullptr, nullptr, 1, command_buffer);
	GraphicsQueue::get_instance()->get_queue()->submit(1, &submit_info, nullptr);

	GraphicsQueue::get_instance()->get_queue()->waitIdle();

	VulkanDevice::get_instance()->get_logical_device()->freeCommandBuffers(
		*SingletonCommandPool::get_instance()->get_command_pool(), 1, command_buffer);
	delete command_buffer;
}
