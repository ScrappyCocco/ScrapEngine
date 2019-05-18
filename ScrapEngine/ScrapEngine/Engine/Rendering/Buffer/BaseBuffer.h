#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseBuffer
		{
		public:
			static void create_buffer(const vk::DeviceSize& size, vk::BufferUsageFlags usage,
			                          vk::MemoryPropertyFlags properties, vk::Buffer& buffer,
			                          vk::DeviceMemory& buffer_memory);

			static void copy_buffer(vk::Buffer* src_buffer, vk::Buffer& dst_buffer, const vk::DeviceSize& size);

			static vk::CommandBuffer* begin_single_time_commands();

			static void end_single_time_commands(vk::CommandBuffer* command_buffer);
		};
	}
}
