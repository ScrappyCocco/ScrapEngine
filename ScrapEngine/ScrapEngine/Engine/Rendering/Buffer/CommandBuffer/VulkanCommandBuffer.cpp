#include <Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h>
#include <Engine/Rendering/RenderPass/VulkanRenderPass.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <imgui.h>

ScrapEngine::Render::VulkanCommandBuffer::~VulkanCommandBuffer()
{
	free_command_buffers();
}

void ScrapEngine::Render::VulkanCommandBuffer::init_command_buffer(
	VulkanFrameBuffer* swap_chain_frame_buffer,
	vk::Extent2D* input_swap_chain_extent_ref,
	VulkanCommandPool* command_pool)
{
	command_pool_ref_ = command_pool;

	const std::vector<vk::Framebuffer>* swap_chain_framebuffers = swap_chain_frame_buffer->
		get_swap_chain_framebuffers_vector();
	command_buffers_.resize(swap_chain_framebuffers->size());

	vk::CommandBufferAllocateInfo alloc_info(
		*command_pool_ref_->get_command_pool(),
		vk::CommandBufferLevel::ePrimary,
		static_cast<uint32_t>(command_buffers_.size())
	);

	if (VulkanDevice::get_instance()->get_logical_device()->allocateCommandBuffers(&alloc_info, command_buffers_.data())
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("[VulkanCommandBuffer] Failed to allocate command buffers!");
	}

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		vk::CommandBufferBeginInfo begin_info(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

		if (command_buffers_[i].begin(&begin_info) != vk::Result::eSuccess)
		{
			throw std::runtime_error("[VulkanCommandBuffer] Failed to begin recording command buffer!");
		}

		render_pass_info_ = vk::RenderPassBeginInfo(
			*VulkanRenderPass::get_instance()->get_render_pass(),
			(*swap_chain_framebuffers)[i],
			vk::Rect2D(vk::Offset2D(), *input_swap_chain_extent_ref)
		);

		std::array<vk::ClearValue, 2> clear_values = {
			vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})),
			vk::ClearDepthStencilValue(1.0f, 0)
		};
		render_pass_info_.clearValueCount = static_cast<uint32_t>(clear_values.size());
		render_pass_info_.pClearValues = clear_values.data();

		command_buffers_[i].beginRenderPass(&render_pass_info_, vk::SubpassContents::eInline);
	}
}

void ScrapEngine::Render::VulkanCommandBuffer::init_current_camera(Camera* current_camera)
{
	current_camera_ = current_camera;
}

void ScrapEngine::Render::VulkanCommandBuffer::load_skybox(VulkanSkyboxInstance* skybox_ref)
{
	vk::DeviceSize offsets[] = {0};
	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
		                                 *skybox_ref->get_skybox_material()->
		                                              get_vulkan_render_graphics_pipeline()->
		                                              get_graphics_pipeline());
		const std::pair<VertexBufferContainer*, IndicesBufferContainer*>*
			skybox_pair = skybox_ref->get_mesh_buffers();
		vk::Buffer buff[] = {*skybox_pair->first->get_buffer()};
		command_buffers_[i].bindVertexBuffers(0, 1, buff, offsets);
		command_buffers_[i].bindIndexBuffer(*skybox_pair->second->get_buffer(), 0, vk::IndexType::eUint32);
		command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
		                                       *skybox_ref->get_skybox_material()->
		                                                    get_vulkan_render_graphics_pipeline()->
		                                                    get_pipeline_layout(),
		                                       0, 1, &(*skybox_ref
		                                                ->get_skybox_material()->
		                                                get_vulkan_render_descriptor_set()->get_descriptor_sets())
		                                       [i],
		                                       0, nullptr);
		command_buffers_[i].drawIndexed(static_cast<uint32_t>(skybox_pair->second->get_vector()->size()),
		                                1,
		                                0, 0, 0);
	}
}

void ScrapEngine::Render::VulkanCommandBuffer::load_mesh(const VulkanMeshInstance* mesh)
{
	//Check if the mesh is visible
	if (!mesh->get_is_visible())
	{
		return;
	}
	//Check if the mesh is in view
	if (!current_camera_->frustum_check_sphere(
		mesh->get_mesh_location().get_glm_vector(),
		mesh->get_mesh_scale().get_max_value() * 5.f))
	{
		return;
	}
	//Add the drawcall for the mesh
	vk::DeviceSize offsets[] = {0};
	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		auto buffers_vector = (*mesh->get_mesh_buffers());
		auto materials_vector = (*mesh->get_mesh_materials());
		bool mesh_has_multi_material = false;
		auto materials_iterator = materials_vector.begin();
		if (mesh->get_mesh_materials()->size() > 1)
		{
			mesh_has_multi_material = true;
		}
		BasicMaterial* current_mat = *materials_iterator;
		for (const auto mesh_buffer : buffers_vector)
		{
			command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
			                                 *current_mat
			                                  ->get_vulkan_render_graphics_pipeline()->get_graphics_pipeline());

			vk::Buffer vertex_buffers[] = {*(mesh_buffer.first->get_buffer())};

			command_buffers_[i].bindVertexBuffers(0, 1, vertex_buffers, offsets);

			command_buffers_[i].bindIndexBuffer(*(mesh_buffer.second->get_buffer()), 0, vk::IndexType::eUint32);

			command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
			                                       *current_mat
			                                        ->get_vulkan_render_graphics_pipeline()->get_pipeline_layout(), 0,
			                                       1,
			                                       &(*current_mat
			                                          ->get_vulkan_render_descriptor_set()->get_descriptor_sets())[i],
			                                       0, nullptr);

			command_buffers_[i].drawIndexed(static_cast<uint32_t>((mesh_buffer.second->get_vector()->size())), 1, 0, 0,
			                                0);

			if (mesh_has_multi_material)
			{
				++materials_iterator;
				if (materials_iterator != materials_vector.end())
				{
					current_mat = *materials_iterator;
				}
			}
		}
	}
}

void ScrapEngine::Render::VulkanCommandBuffer::load_ui(VulkanImGui* gui)
{
	gui->new_frame();

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

		if (im_draw_data->CmdListsCount > 0) {
			vk::DeviceSize offsets[1] = { 0 };

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
					scissor_offset.setX(std::max((int32_t)(pcmd->ClipRect.x), 0));
					scissor_offset.setY(std::max((int32_t)(pcmd->ClipRect.y), 0));
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

void ScrapEngine::Render::VulkanCommandBuffer::close_command_buffer()
{
	for (auto& command_buffer : command_buffers_)
	{
		command_buffer.endRenderPass();

		command_buffer.end();
	}
}

void ScrapEngine::Render::VulkanCommandBuffer::free_command_buffers()
{
	if (!command_buffers_.empty())
	{
		VulkanDevice::get_instance()->get_logical_device()->freeCommandBuffers(
			*command_pool_ref_->get_command_pool(),
			static_cast<uint32_t>(command_buffers_.size()),
			command_buffers_.data());
		command_buffers_.clear();
	}
}

const std::vector<vk::CommandBuffer>* ScrapEngine::Render::VulkanCommandBuffer::get_command_buffers_vector() const
{
	return &command_buffers_;
}
