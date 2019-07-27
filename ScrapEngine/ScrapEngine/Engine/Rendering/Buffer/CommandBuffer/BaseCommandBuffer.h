#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseCommandBuffer
		{
		protected:
			std::vector<vk::CommandBuffer> command_buffers_;
			vk::RenderPassBeginInfo render_pass_info_;
			VulkanCommandPool* command_pool_ref_;
		public:
			BaseCommandBuffer() = default;

			virtual ~BaseCommandBuffer() = 0;

			void close_command_buffer();

			void free_command_buffers();

			const std::vector<vk::CommandBuffer>* get_command_buffers_vector() const;
		};
	}
}
