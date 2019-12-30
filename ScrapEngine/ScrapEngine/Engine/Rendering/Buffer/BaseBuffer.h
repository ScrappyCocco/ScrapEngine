#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseBuffer
		{
		public:
			static void create_buffer(const vk::DeviceSize& size, const vk::BufferUsageFlags& usage,
			                          const vk::MemoryPropertyFlags& properties, vk::Buffer& buffer,
			                          vk::DeviceMemory& buffer_memory, bool auto_bind_memory = true);

			//-------------
			//Utils methods to works and copy stuff from/with buffers
			//Every method use begin_single_time_command() and end_and_submit_single_time_command()

			static void copy_buffer(vk::Buffer* src_buffer, vk::Buffer& dst_buffer, const vk::DeviceSize& size,
			                        const vk::DeviceSize& scr_offset = 0, const vk::DeviceSize& dst_offset = 0,
			                        uint32_t region_count = 1);

			static void copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
			                                 vk::BufferImageCopy* region, int regioncount,
			                                 vk::ImageLayout layout);

			//Return a new command buffer that can be used for simple commands (ex: copying stuff)
			//This command buffer is for a SINGLE submission only
			static std::unique_ptr<vk::CommandBuffer> begin_single_time_command();

			//Submit the command buffer to the queue
			static void end_and_submit_single_time_command(const std::unique_ptr<vk::CommandBuffer>& command_buffer);
		};
	}
}
