#include <Engine/Rendering/Buffer/CommandBuffer/StandardCommandBuffer/StandardCommandBuffer.h>
#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

void ScrapEngine::Render::StandardCommandBuffer::init_command_buffer(
	ScrapEngine::Render::VulkanFrameBuffer* swap_chain_frame_buffer,
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
			*StandardRenderPass::get_instance()->get_render_pass(),
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

void ScrapEngine::Render::StandardCommandBuffer::load_mesh(VulkanMeshInstance* mesh)
{
	//Do not include mesh to delete
	if(mesh->get_pending_deletion())
	{
		mesh->increase_deletion_counter();
		return;
	}
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
