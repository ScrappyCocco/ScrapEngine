#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanModelPool/VulkanModelPool.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanModelBuffersPool/VulkanModelBuffersPool.h>

ScrapEngine::Render::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path,
                                                            const std::string& fragment_shader_path,
                                                            const std::string& model_path,
                                                            const std::vector<std::string>& textures_path,
                                                            VulkanSwapChain* swap_chain)
{
	//CREATE UNIFORM BUFFER
	vulkan_render_uniform_buffer_ = new StandardUniformBuffer(swap_chain->get_swap_chain_images_vector()->size());
	vulkan_render_model_ = VulkanModelPool::get_instance()->get_model(model_path);
	if (vulkan_render_model_->get_meshes()->size() != textures_path.size() && textures_path.size() > 1)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "The texture array must have size 1 or equal number of meshes ("
		                             + std::to_string(vulkan_render_model_->get_meshes()->size()) + ")");
	}
	for (const auto& texture_path : textures_path)
	{
		//CREATE MATERIAL(S)
		SimpleMaterial* material = new SimpleMaterial();
		material->create_pipeline(vertex_shader_path, fragment_shader_path, swap_chain);
		material->create_texture(texture_path);
		material->create_descriptor_sets(swap_chain, vulkan_render_uniform_buffer_);
		model_materials_.push_back(material);
	}
	mesh_buffers_ = VulkanModelBuffersPool::get_instance()->get_model_buffers(model_path, vulkan_render_model_);
}

ScrapEngine::Render::VulkanMeshInstance::~VulkanMeshInstance()
{
	// Delete the textures
	for (auto material : model_materials_)
	{
		delete material;
	}
	// Delete the uniform buffer
	delete vulkan_render_uniform_buffer_;
	//Shadowmapping resources
	delete shadowmapping_descriptor_set_;
	delete shadowmapping_descriptor_pool_;
	delete shadowmapping_uniform_buffer_;
}

void ScrapEngine::Render::VulkanMeshInstance::set_mesh_location(const Core::SVector3& location)
{
	object_location_.set_position(location);
}

void ScrapEngine::Render::VulkanMeshInstance::set_mesh_rotation(const Core::SVector3& rotation)
{
	object_location_.set_rotation(rotation);
}

void ScrapEngine::Render::VulkanMeshInstance::set_mesh_scale(const Core::SVector3& scale)
{
	object_location_.set_scale(scale);
}

ScrapEngine::Core::SVector3 ScrapEngine::Render::VulkanMeshInstance::get_mesh_location() const
{
	return object_location_.get_position();
}

ScrapEngine::Core::SVector3 ScrapEngine::Render::VulkanMeshInstance::get_mesh_rotation() const
{
	return object_location_.get_rotation();
}

ScrapEngine::Core::SVector3 ScrapEngine::Render::VulkanMeshInstance::get_mesh_scale() const
{
	return object_location_.get_scale();
}

bool ScrapEngine::Render::VulkanMeshInstance::get_is_static() const
{
	return is_static_;
}

void ScrapEngine::Render::VulkanMeshInstance::set_is_static(const bool is_static)
{
	is_static_ = is_static;
}

bool ScrapEngine::Render::VulkanMeshInstance::get_is_visible() const
{
	return is_visible_;
}

void ScrapEngine::Render::VulkanMeshInstance::set_is_visible(const bool visible)
{
	is_visible_ = visible;
}

bool ScrapEngine::Render::VulkanMeshInstance::get_cast_shadows() const
{
	return cast_shadows_;
}

void ScrapEngine::Render::VulkanMeshInstance::set_cast_shadows(const bool cast)
{
	cast_shadows_ = cast;
}

bool ScrapEngine::Render::VulkanMeshInstance::get_frustum_check() const
{
	return frustum_check_;
}

void ScrapEngine::Render::VulkanMeshInstance::set_frustum_check(const bool should_check)
{
	frustum_check_ = should_check;
}

void ScrapEngine::Render::VulkanMeshInstance::set_for_deletion()
{
	pending_deletion_ = true;
}

bool ScrapEngine::Render::VulkanMeshInstance::get_pending_deletion() const
{
	return pending_deletion_;
}

void ScrapEngine::Render::VulkanMeshInstance::increase_deletion_counter()
{
	deletion_counter_++;
}

uint16_t ScrapEngine::Render::VulkanMeshInstance::get_deletion_counter() const
{
	return deletion_counter_;
}

void ScrapEngine::Render::VulkanMeshInstance::init_shadowmapping_resources(StandardShadowmapping* shadowmapping)
{
	const size_t size = vulkan_render_uniform_buffer_->get_uniform_buffers()->size();

	shadowmapping_uniform_buffer_ = new ShadowmappingUniformBuffer(size);
	shadowmapping_descriptor_set_ = new ShadowmappingDescriptorSet();

	shadowmapping_descriptor_pool_ = new StandardDescriptorPool(size);
	shadowmapping_descriptor_set_->create_descriptor_sets(
		shadowmapping_descriptor_pool_->get_descriptor_pool(),
		size,
		shadowmapping_uniform_buffer_->get_uniform_buffers(),
		sizeof(OffscreenUniformBufferObject)
	);

	write_depth_descriptor(shadowmapping);
}

void ScrapEngine::Render::VulkanMeshInstance::write_depth_descriptor(StandardShadowmapping* shadowmapping)
{
	vk::ImageView* imageview = shadowmapping->get_offscreen_frame_buffer()->get_depth_attachment()->get_image_view();
	vk::Sampler* sampler = shadowmapping->get_offscreen_frame_buffer()->get_depth_sampler();

	const vk::DescriptorImageInfo image_info(
		*sampler,
		*imageview,
		vk::ImageLayout::eDepthStencilReadOnlyOptimal
	);

	for (auto& material : model_materials_)
	{
		material->get_vulkan_render_descriptor_set()->write_image_info(image_info, 1);
	}
}

void ScrapEngine::Render::VulkanMeshInstance::update_uniform_buffer(const uint32_t& current_image,
                                                                    Camera* render_camera,
                                                                    const glm::vec3& light_pos)
{
	//update_shadowmap_uniform_buffer should be called first to update shadow_depth_bias
	const glm::mat4 shadow_depth_bias = shadowmapping_uniform_buffer_->get_depth_bias();
	//Standard update
	if (is_static_)
	{
		if (transform_dirty_)
		{
			vulkan_render_uniform_buffer_->update_uniform_buffer(current_image,
			                                                     object_location_,
			                                                     render_camera,
			                                                     light_pos,
			                                                     shadow_depth_bias
			);
			transform_dirty_ = false;
		}
		else
		{
			vulkan_render_uniform_buffer_->update_uniform_buffer(current_image,
			                                                     object_location_,
			                                                     render_camera,
			                                                     light_pos, shadow_depth_bias,
			                                                     false
			);
		}
	}
	else
	{
		vulkan_render_uniform_buffer_->update_uniform_buffer(current_image,
		                                                     object_location_,
		                                                     render_camera,
		                                                     light_pos,
		                                                     shadow_depth_bias
		);
	}
}

void ScrapEngine::Render::VulkanMeshInstance::update_shadowmap_uniform_buffer(const uint32_t& current_image,
                                                                              StandardShadowmapping* shadowmap_info)
const
{
	const glm::vec3 light_pos = shadowmap_info->get_light_pos();
	const glm::vec3 light_look_at = shadowmap_info->get_light_look_at();
	const float light_fov = shadowmap_info->get_light_fov();
	const float z_far = shadowmap_info->get_z_far();
	const float z_near = shadowmap_info->get_z_near();

	if (is_static_)
	{
		if (transform_dirty_)
		{
			shadowmapping_uniform_buffer_->update_uniform_buffer(
				current_image,
				object_location_,
				true,
				light_fov,
				light_pos,
				light_look_at,
				z_near,
				z_far
			);
		}
		else
		{
			shadowmapping_uniform_buffer_->update_uniform_buffer(
				current_image,
				object_location_,
				false,
				light_fov,
				light_pos,
				light_look_at,
				z_near,
				z_far
			);
		}
	}
	else
	{
		shadowmapping_uniform_buffer_->update_uniform_buffer(
			current_image,
			object_location_,
			true,
			light_fov,
			light_pos,
			light_look_at,
			z_near,
			z_far
		);
	}
}

ScrapEngine::Render::StandardUniformBuffer* ScrapEngine::Render::VulkanMeshInstance::
get_vulkan_render_uniform_buffer() const
{
	return vulkan_render_uniform_buffer_;
}

const std::vector<ScrapEngine::Render::BasicMaterial*>* ScrapEngine::Render::VulkanMeshInstance::
get_mesh_materials() const
{
	return &model_materials_;
}

ScrapEngine::Render::ShadowmappingUniformBuffer* ScrapEngine::Render::VulkanMeshInstance::
get_shadowmapping_uniform_buffer() const
{
	return shadowmapping_uniform_buffer_;
}

ScrapEngine::Render::ShadowmappingDescriptorSet* ScrapEngine::Render::VulkanMeshInstance::
get_shadowmapping_descriptor_set() const
{
	return shadowmapping_descriptor_set_;
}

std::shared_ptr<std::vector<
	std::pair<
		ScrapEngine::Render::VertexBufferContainer*,
		ScrapEngine::Render::IndicesBufferContainer*>
>> ScrapEngine::Render::VulkanMeshInstance::get_mesh_buffers() const
{
	return mesh_buffers_;
}
