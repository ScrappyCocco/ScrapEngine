#include <Engine/Rendering/Buffer/CommandBuffer/StandardCommandBuffer/StandardCommandBuffer.h>
#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

void ScrapEngine::Render::StandardCommandBuffer::pre_shadow_mesh_commands(StandardShadowmapping* shadowmapping)
{
	const vk::Extent2D shadow_map_extent = StandardShadowmapping::get_shadow_map_extent();
	const vk::Rect2D rect = vk::Rect2D(vk::Offset2D(), shadow_map_extent);

	for (auto& command_buffer : command_buffers_)
	{
		//Viewport

		vk::Viewport viewport;
		viewport.setWidth(static_cast<float>(shadow_map_extent.width));
		viewport.setHeight(static_cast<float>(shadow_map_extent.height));
		viewport.setMinDepth(0.0f);
		viewport.setMaxDepth(1.0f);

		command_buffer.setViewport(0, 1, &viewport);

		//Scissors
		command_buffer.setScissor(0, 1, &rect);

		// Set depth bias
		// Required to avoid shadow mapping artefacts
		command_buffer.setDepthBias(
			shadowmapping->get_depth_bias_constant(),
			0.0f,
			shadowmapping->get_depth_bias_slope()
		);
	}
}

ScrapEngine::Render::StandardCommandBuffer::StandardCommandBuffer(VulkanCommandPool* command_pool,
                                                                  const int16_t cb_size)
{
	command_pool_ref_ = command_pool;

	command_buffers_.resize(cb_size);

	vk::CommandBufferAllocateInfo alloc_info(
		*command_pool_ref_,
		vk::CommandBufferLevel::ePrimary,
		static_cast<uint32_t>(command_buffers_.size())
	);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->allocateCommandBuffers(&alloc_info, command_buffers_.data());

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "[VulkanCommandBuffer] Failed to allocate command buffers!");
	}
}

void ScrapEngine::Render::StandardCommandBuffer::init_shadow_map(StandardShadowmapping* shadowmapping)
{
	std::array<vk::ClearValue, 1> clear_values = {
		vk::ClearDepthStencilValue(1.0f, 0)
	};
	const std::vector<vk::Framebuffer>* offscreen_framebuffers = shadowmapping
	                                                             ->get_offscreen_frame_buffer()->
	                                                             get_framebuffers_vector();
	const vk::Extent2D shadow_map_extent = StandardShadowmapping::get_shadow_map_extent();
	const vk::Rect2D rect = vk::Rect2D(vk::Offset2D(), shadow_map_extent);

	for (auto& command_buffer : command_buffers_)
	{
		//Begin

		vk::RenderPassBeginInfo begin_info(
			*shadowmapping->get_offscreen_render_pass()->get_render_pass(),
			(*offscreen_framebuffers)[0],
			rect
		);

		begin_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
		begin_info.pClearValues = clear_values.data();

		command_buffer.beginRenderPass(&begin_info, vk::SubpassContents::eInline);
	}
}

void ScrapEngine::Render::StandardCommandBuffer::load_mesh_shadow_map(StandardShadowmapping* shadowmapping,
                                                                      VulkanMeshInstance* mesh)
{
	//Do not include mesh to delete
	if (mesh->get_pending_deletion())
	{
		//Do NOT increase the deletion counter in the shadow map loading
		return;
	}
	//Check if the mesh is visible
	if (!mesh->get_is_visible())
	{
		return;
	}
	//Check if the mesh has shadow rendering
	if (!mesh->get_cast_shadows())
	{
		return;
	}
	if (mesh->get_frustum_check())
	{
		//Check if the mesh is in view
		if (!current_camera_->frustum_check_sphere(
			mesh->get_mesh_location().get_glm_vector(),
			mesh->get_mesh_scale().get_max_value() * frustum_sphere_radius_multiplier_ * 2))
		{
			return;
		}
	}
	//Add the drawcall for the mesh in the depth pass (shadow rendering)
	const vk::DeviceSize offsets[] = {0};
	auto buffers_vector = (*mesh->get_mesh_buffers());

	pre_shadow_mesh_commands(shadowmapping);

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		for (const auto mesh_buffer : buffers_vector)
		{
			command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
			                                 *shadowmapping->get_offscreen_pipeline()->get_graphics_pipeline()
			);

			command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
			                                       *shadowmapping->get_offscreen_pipeline()->get_pipeline_layout(),
			                                       0,
			                                       1,
			                                       &(*mesh->get_shadowmapping_descriptor_set()->
			                                                get_descriptor_sets())[i],
			                                       0,
			                                       nullptr
			);

			vk::Buffer vertex_buffers[] = {*(mesh_buffer.first)};

			command_buffers_[i].bindVertexBuffers(0, 1, vertex_buffers, offsets);

			command_buffers_[i].bindIndexBuffer(*(mesh_buffer.second), 0, vk::IndexType::eUint32);

			command_buffers_[i].drawIndexed(static_cast<uint32_t>((mesh_buffer.second->get_vector()->size())), 1, 0, 0,
			                                0);
		}
	}
}

void ScrapEngine::Render::StandardCommandBuffer::init_command_buffer(
	vk::Extent2D* input_swap_chain_extent_ref, BaseFrameBuffer* swap_chain_frame_buffer)
{
	const std::vector<vk::Framebuffer>* swap_chain_framebuffers = swap_chain_frame_buffer->
		get_framebuffers_vector();

	std::array<vk::ClearValue, 2> clear_values = {
		vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f}),
		vk::ClearDepthStencilValue(1.0f, 0)
	};

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		render_pass_info_ = vk::RenderPassBeginInfo(
			*StandardRenderPass::get_instance(),
			(*swap_chain_framebuffers)[i],
			vk::Rect2D(vk::Offset2D(), *input_swap_chain_extent_ref)
		);

		render_pass_info_.clearValueCount = static_cast<uint32_t>(clear_values.size());
		render_pass_info_.pClearValues = clear_values.data();

		command_buffers_[i].beginRenderPass(&render_pass_info_, vk::SubpassContents::eInline);
	}
}

void ScrapEngine::Render::StandardCommandBuffer::init_current_camera(Camera* current_camera)
{
	current_camera_ = current_camera;
}

void ScrapEngine::Render::StandardCommandBuffer::load_skybox(VulkanSkyboxInstance* skybox_ref)
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
		vk::Buffer buff[] = {*(skybox_pair->first)};
		command_buffers_[i].bindVertexBuffers(0, 1, buff, offsets);
		command_buffers_[i].bindIndexBuffer(*(skybox_pair->second), 0, vk::IndexType::eUint32);
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

void ScrapEngine::Render::StandardCommandBuffer::load_mesh(VulkanMeshInstance* mesh)
{
	//Do not include mesh to delete
	if (mesh->get_pending_deletion())
	{
		mesh->increase_deletion_counter();
		return;
	}
	//Check if the mesh is visible
	if (!mesh->get_is_visible())
	{
		return;
	}
	if (mesh->get_frustum_check())
	{
		//Check if the mesh is in view
		if (!current_camera_->frustum_check_sphere(
			mesh->get_mesh_location().get_glm_vector(),
			mesh->get_mesh_scale().get_max_value() * frustum_sphere_radius_multiplier_))
		{
			return;
		}
	}
	//Add the drawcall for the mesh
	const vk::DeviceSize offsets[] = {0};
	auto buffers_vector = (*mesh->get_mesh_buffers());
	auto materials_vector = (*mesh->get_mesh_materials());

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
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

			vk::Buffer vertex_buffers[] = {*(mesh_buffer.first)};

			command_buffers_[i].bindVertexBuffers(0, 1, vertex_buffers, offsets);

			command_buffers_[i].bindIndexBuffer(*(mesh_buffer.second), 0, vk::IndexType::eUint32);

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
