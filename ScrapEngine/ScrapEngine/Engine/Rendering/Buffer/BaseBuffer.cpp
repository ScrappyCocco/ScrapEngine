#include "BaseBuffer.h"

#include <stdexcept>
#include "../Memory/MemoryManager.h"
#include "../Base/StaticTypes.h"

void ScrapEngine::Render::BaseBuffer::create_buffer(const vk::DeviceSize& size, vk::BufferUsageFlags usage,
                                                    vk::MemoryPropertyFlags properties, vk::Buffer& buffer,
                                                    vk::DeviceMemory& buffer_memory)
{
	vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		size,
		usage,
		vk::SharingMode::eExclusive
	);

	if (VulkanDevice::StaticLogicDeviceRef->createBuffer(&buffer_info, nullptr, &buffer) != vk::Result::eSuccess)
	{
		throw std::runtime_error("BaseBuffer: Failed to create buffer!");
	}

	vk::MemoryRequirements mem_requirements;
	VulkanDevice::StaticLogicDeviceRef->getBufferMemoryRequirements(buffer, &mem_requirements);

	vk::MemoryAllocateInfo alloc_info(mem_requirements.size,
	                                  findMemoryType(mem_requirements.memoryTypeBits, properties));

	if (VulkanDevice::StaticLogicDeviceRef->allocateMemory(&alloc_info, nullptr, &buffer_memory) != vk::Result::eSuccess
	)
	{
		throw std::runtime_error("BaseBuffer: Failed to allocate buffer memory!");
	}

	VulkanDevice::StaticLogicDeviceRef->bindBufferMemory(buffer, buffer_memory, 0);
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
	vk::CommandBufferAllocateInfo alloc_info(*VulkanCommandPool::static_command_pool_ref, vk::CommandBufferLevel::ePrimary,
	                                         1);

	vk::CommandBuffer* command_buffer = new vk::CommandBuffer();
	VulkanDevice::StaticLogicDeviceRef->allocateCommandBuffers(&alloc_info, command_buffer);

	const vk::CommandBufferBeginInfo begin_info(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

	command_buffer->begin(begin_info);

	return command_buffer;
}

void ScrapEngine::Render::BaseBuffer::end_single_time_commands(vk::CommandBuffer* command_buffer)
{
	command_buffer->end();

	vk::SubmitInfo submit_info(0, nullptr, nullptr, 1, command_buffer);
	GraphicsQueue::StaticGraphicsQueueRef->submit(1, &submit_info, nullptr);

	GraphicsQueue::StaticGraphicsQueueRef->waitIdle();

	VulkanDevice::StaticLogicDeviceRef->freeCommandBuffers(*VulkanCommandPool::static_command_pool_ref, 1, command_buffer);
	delete command_buffer;
}
