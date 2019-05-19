#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <Engine/Rendering/Pipeline/VulkanGraphicsPipeline.h>
#include <Engine/Rendering/Model/VulkanSkyboxInstance.h>
#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>
#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSkyboxInstance;

		class VulkanCommandBuffer
		{
		private:
			std::vector<vk::CommandBuffer> command_buffers_;
		public:

			VulkanCommandBuffer(ScrapEngine::Render::VulkanFrameBuffer* swap_chain_frame_buffer,
			                    vk::Extent2D* input_swap_chain_extent_ref,
			                    std::vector<ScrapEngine::Render::VulkanGraphicsPipeline*> input_vulkan_pipeline_ref,
			                    const std::vector<const std::vector<vk::DescriptorSet>*>& descriptor_sets,
								const std::vector<
				const std::vector<
				std::pair<ScrapEngine::Render::VertexBufferContainer*, ScrapEngine::Render::IndicesBufferContainer*>
				>*>&
			                    mesh_buffers,
			                    ScrapEngine::Render::VulkanSkyboxInstance* skybox_ref = nullptr);

			~VulkanCommandBuffer();

			void free_command_buffers();

			const std::vector<vk::CommandBuffer>* get_command_buffers_vector() const;
		};
	}
}
