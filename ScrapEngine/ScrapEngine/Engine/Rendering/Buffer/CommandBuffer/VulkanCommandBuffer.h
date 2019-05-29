#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanCommandBuffer
		{
		private:
			std::vector<vk::CommandBuffer> command_buffers_;
			vk::RenderPassBeginInfo render_pass_info_;
		public:

			VulkanCommandBuffer() = default;

			~VulkanCommandBuffer();

			void init_command_buffer(VulkanFrameBuffer* swap_chain_frame_buffer,
			                         vk::Extent2D* input_swap_chain_extent_ref);
			void load_skybox(VulkanSkyboxInstance* skybox_ref);
			void load_mesh(const VulkanMeshInstance* mesh);
			void close_command_buffer();

			void free_command_buffers();

			const std::vector<vk::CommandBuffer>* get_command_buffers_vector() const;
		};
	}
}
