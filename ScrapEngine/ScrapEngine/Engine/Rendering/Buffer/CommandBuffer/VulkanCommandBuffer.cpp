#include <Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h>
#include <Engine/Rendering/Base/StaticTypes.h>

ScrapEngine::Render::VulkanCommandBuffer::VulkanCommandBuffer(
	ScrapEngine::Render::VulkanFrameBuffer* swap_chain_frame_buffer, vk::Extent2D* input_swap_chain_extent_ref,
	std::vector<ScrapEngine::Render::VulkanGraphicsPipeline*> input_vulkan_pipeline_ref,
	const std::vector<const std::vector<vk::DescriptorSet>*>& descriptor_sets,
	const std::vector<std::pair<VertexBufferContainer*, IndicesBufferContainer*>>& mesh_buffers,
	ScrapEngine::Render::VulkanSkyboxInstance* skybox_ref)
{
	const std::vector<vk::Framebuffer>* swap_chain_framebuffers = swap_chain_frame_buffer->
		get_swap_chain_framebuffers_vector();
	command_buffers_.resize(swap_chain_framebuffers->size());

	vk::CommandBufferAllocateInfo alloc_info(
		*VulkanCommandPool::static_command_pool_ref,
		vk::CommandBufferLevel::ePrimary,
		static_cast<uint32_t>(command_buffers_.size())
	);

	if (VulkanDevice::static_logic_device_ref->allocateCommandBuffers(&alloc_info, command_buffers_.data()) != vk::
		Result::
		eSuccess)
	{
		throw std::runtime_error("VulkanCommandBuffer: Failed to allocate command buffers!");
	}

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		vk::CommandBufferBeginInfo begin_info(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

		if (command_buffers_[i].begin(&begin_info) != vk::Result::eSuccess)
		{
			throw std::runtime_error("VulkanCommandBuffer: Failed to begin recording command buffer!");
		}

		vk::RenderPassBeginInfo render_pass_info(
			*VulkanRenderPass::static_render_pass_ref,
			(*swap_chain_framebuffers)[i],
			vk::Rect2D(vk::Offset2D(), *input_swap_chain_extent_ref)
		);

		std::array<vk::ClearValue, 2> clear_values = {
			vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})),
			vk::ClearDepthStencilValue(1.0f, 0)
		};
		render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
		render_pass_info.pClearValues = clear_values.data();

		command_buffers_[i].beginRenderPass(&render_pass_info, vk::SubpassContents::eInline);

		vk::DeviceSize offsets[] = {0};

		//Skybox render, must be before the rest of the render
		if (skybox_ref)
		{
			command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
			                                 *skybox_ref->get_vulkan_render_graphics_pipeline()->
			                                              get_graphics_pipeline());
			const std::pair<ScrapEngine::Render::VertexBufferContainer*, ScrapEngine::Render::IndicesBufferContainer*>* skybox_pair = skybox_ref->get_mesh_buffers();
			vk::Buffer buff[] = { *skybox_pair->first->get_buffer()};
			command_buffers_[i].bindVertexBuffers(0, 1, buff, offsets);
			command_buffers_[i].bindIndexBuffer(*skybox_pair->second->get_buffer(), 0, vk::IndexType::eUint32);
			command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
			                                       *skybox_ref->get_vulkan_render_graphics_pipeline()->
			                                                    get_pipeline_layout(),
			                                       0, 1, &(*skybox_ref
			                                                ->get_vulkan_render_descriptor_set()->get_descriptor_sets())
			                                       [i],
			                                       0, nullptr);
			command_buffers_[i].drawIndexed(static_cast<uint32_t>(skybox_pair->second->get_vector()->size()),
			                                1,
			                                0, 0, 0);
		}
		//Scene render
		for (unsigned int k = 0; k < mesh_buffers.size(); k++)
		{
			command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
			                                 *input_vulkan_pipeline_ref[k]->get_graphics_pipeline());

			//vk::Buffer vertex_buffers[] = {*(*mesh_buffers[k]).first.};
			vk::Buffer vertex_buffers[] = { *(mesh_buffers[k].first->get_buffer()) };

			command_buffers_[i].bindVertexBuffers(0, 1, vertex_buffers, offsets);

			command_buffers_[i].bindIndexBuffer(*(mesh_buffers[k].second->get_buffer()), 0, vk::IndexType::eUint32);

			command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
			                                       *input_vulkan_pipeline_ref[k]->get_pipeline_layout(), 0, 1,
			                                       &(*descriptor_sets[k])[i], 0, nullptr);

			command_buffers_[i].drawIndexed(static_cast<uint32_t>((mesh_buffers[k].second->get_vector()->size())), 1, 0, 0, 0);
		}

		command_buffers_[i].endRenderPass();

		command_buffers_[i].end();
	}
}

ScrapEngine::Render::VulkanCommandBuffer::~VulkanCommandBuffer()
{
	free_command_buffers();
}

void ScrapEngine::Render::VulkanCommandBuffer::free_command_buffers()
{
	VulkanDevice::static_logic_device_ref->freeCommandBuffers(*VulkanCommandPool::static_command_pool_ref,
	                                                          static_cast<uint32_t>(command_buffers_.size()),
	                                                          command_buffers_.data());
	command_buffers_.clear();
}

const std::vector<vk::CommandBuffer>* ScrapEngine::Render::VulkanCommandBuffer::get_command_buffers_vector() const
{
	return &command_buffers_;
}
