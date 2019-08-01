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
	vulkan_render_uniform_buffer_ = new UniformBuffer(swap_chain->get_swap_chain_images_vector(),
	                                                  swap_chain->get_swap_chain_extent());
	vulkan_render_model_ = VulkanModelPool::get_instance()->get_model(model_path);
	if (vulkan_render_model_->get_meshes()->size() != textures_path.size() && textures_path.size() > 1)
	{
		throw std::runtime_error("The texture array must have size 1 or equal number of meshes ("
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

void ScrapEngine::Render::VulkanMeshInstance::update_uniform_buffer(const uint32_t& current_image,
                                                                    Camera* render_camera)
{
	if(is_static_){
		if(transform_dirty_)
		{
			vulkan_render_uniform_buffer_->update_uniform_buffer(current_image, object_location_, render_camera);
			transform_dirty_ = false;
		}else
		{
			vulkan_render_uniform_buffer_->update_uniform_buffer(current_image, object_location_, render_camera, false);
		}
	}else
	{
		vulkan_render_uniform_buffer_->update_uniform_buffer(current_image, object_location_, render_camera);
	}
}

ScrapEngine::Render::UniformBuffer* ScrapEngine::Render::VulkanMeshInstance::get_vulkan_render_uniform_buffer() const
{
	return vulkan_render_uniform_buffer_;
}

const std::vector<ScrapEngine::Render::BasicMaterial*>* ScrapEngine::Render::VulkanMeshInstance::
get_mesh_materials() const
{
	return &model_materials_;
}

std::shared_ptr<std::vector<
	std::pair<
		ScrapEngine::Render::VertexBufferContainer*,
		ScrapEngine::Render::IndicesBufferContainer*>
>> ScrapEngine::Render::VulkanMeshInstance::get_mesh_buffers() const
{
	return mesh_buffers_;
}
