#include <Engine/Rendering/Buffer/CommandBuffer/GuiCommandBuffer/GuiCommandBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <imgui.h>

ScrapEngine::Render::GuiCommandBuffer::GuiCommandBuffer(BaseRenderPass* render_pass, VulkanCommandPool* command_pool)
	: render_pass_ref_(render_pass)
{
	command_pool_ref_ = command_pool;

	//Optimize the GuiCommandBuffer generating only 1 command buffer instead of 3
	//This because the GuiCommandBuffer is rebuilt every frame
	//So it has no sense to allocate and build 2 unused command buffers
	command_buffers_.resize(1);

	vk::CommandBufferAllocateInfo alloc_info(
		*command_pool_ref_,
		vk::CommandBufferLevel::ePrimary,
		static_cast<uint32_t>(1)
	);

	if (VulkanDevice::get_instance()->get_logical_device()->allocateCommandBuffers(&alloc_info, command_buffers_.data())
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("[VulkanCommandBuffer] Failed to allocate command buffers!");
	}
}

void ScrapEngine::Render::GuiCommandBuffer::init_command_buffer(
	BaseFrameBuffer* swap_chain_frame_buffer,
	vk::Extent2D* input_swap_chain_extent_ref,
	const uint32_t current_image)
{
	const std::vector<vk::Framebuffer>* swap_chain_framebuffers = swap_chain_frame_buffer->
		get_framebuffers_vector();

	for (auto& command_buffer : command_buffers_)
	{
		render_pass_info_ = vk::RenderPassBeginInfo(
			*render_pass_ref_,
			//So here i read the frame buffer corresponding to the next image frame
			//It must be passed as parameter from the Render Manager
			(*swap_chain_framebuffers)[current_image],
			vk::Rect2D(vk::Offset2D(), *input_swap_chain_extent_ref)
		);

		//Don't clear the frame
		render_pass_info_.clearValueCount = 0;

		command_buffer.beginRenderPass(&render_pass_info_, vk::SubpassContents::eInline);
	}
}

void ScrapEngine::Render::GuiCommandBuffer::load_ui(VulkanImGui* gui)
{
	//Update buffers
	gui->update_buffers();

	ImGuiIO& io = ImGui::GetIO();

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
		                                       *gui->get_pipeline()->get_pipeline_layout(), 0, 1,
		                                       &(*gui->get_descriptor_set()->get_descriptor_sets())[i], 0, nullptr);

		command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
		                                 *gui->get_pipeline()->get_graphics_pipeline());

		vk::Viewport viewport;
		viewport.setWidth(ImGui::GetIO().DisplaySize.x);
		viewport.setHeight(ImGui::GetIO().DisplaySize.y);
		viewport.setMinDepth(0.0f);
		viewport.setMaxDepth(1.0f);
		command_buffers_[i].setViewport(0, 1, &viewport);

		VulkanImGui::PushConstBlock* const_block = gui->get_push_const_block();
		const_block->scale = glm::vec2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
		const_block->translate = glm::vec2(-1.0f);
		command_buffers_[i].pushConstants(*gui->get_pipeline()->get_pipeline_layout(), vk::ShaderStageFlagBits::eVertex,
		                                  0, sizeof(VulkanImGui::PushConstBlock), const_block);

		ImDrawData* im_draw_data = ImGui::GetDrawData();
		int32_t vertex_offset = 0;
		int32_t index_offset = 0;

		if (im_draw_data->CmdListsCount > 0)
		{
			vk::DeviceSize offsets[1] = {0};

			command_buffers_[i].bindVertexBuffers(0, 1, gui->get_vertex_buffer()->get_buffer(), offsets);
			command_buffers_[i].bindIndexBuffer(*gui->get_index_buffer()->get_buffer(), 0, vk::IndexType::eUint16);

			for (int32_t k = 0; k < im_draw_data->CmdListsCount; k++)
			{
				const ImDrawList* cmd_list = im_draw_data->CmdLists[k];
				for (int32_t j = 0; j < cmd_list->CmdBuffer.Size; j++)
				{
					const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[j];
					vk::Rect2D scissor_rect;
					vk::Offset2D scissor_offset;
					vk::Extent2D scissor_extend;
					scissor_offset.setX(std::max(static_cast<int32_t>(pcmd->ClipRect.x), 0));
					scissor_offset.setY(std::max(static_cast<int32_t>(pcmd->ClipRect.y), 0));
					scissor_rect.setOffset(scissor_offset);
					scissor_extend.setWidth(static_cast<uint32_t>(pcmd->ClipRect.z - pcmd->ClipRect.x));
					scissor_extend.setHeight(static_cast<uint32_t>(pcmd->ClipRect.w - pcmd->ClipRect.y));
					scissor_rect.setExtent(scissor_extend);

					command_buffers_[i].setScissor(0, 1, &scissor_rect);
					command_buffers_[i].drawIndexed(pcmd->ElemCount, 1, index_offset, vertex_offset, 0);
					index_offset += pcmd->ElemCount;
				}
				vertex_offset += cmd_list->VtxBuffer.Size;
			}
		}
	}
}
