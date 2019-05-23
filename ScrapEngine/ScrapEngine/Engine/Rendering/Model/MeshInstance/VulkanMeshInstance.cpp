#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanModelPool/VulkanModelPool.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanModelBuffersPool/VulkanModelBuffersPool.h>

ScrapEngine::Render::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path,
                                                            const std::string& fragment_shader_path,
                                                            const std::string& model_path,
                                                            const std::vector<std::string>& textures_path,
                                                            ScrapEngine::Render::VulkanSwapChain* swap_chain)
{
	//CREATE UNIFORM BUFFER
	vulkan_render_uniform_buffer_ = new UniformBuffer(swap_chain->get_swap_chain_images_vector(),
	                                                  swap_chain->get_swap_chain_extent());
	Debug::DebugLog::print_to_console_log("UniformBuffer created");
	vulkan_render_model_ = VulkanModelPool::get_instance()->get_model(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	if (vulkan_render_model_->get_meshes()->size() != textures_path.size() && textures_path.size() > 1)
	{
		throw std::runtime_error("The texture array must have size 1 or equal number of meshes!");
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

void ScrapEngine::Render::VulkanMeshInstance::set_mesh_location(const glm::vec3& location)
{
	object_location_.location = location;
}

void ScrapEngine::Render::VulkanMeshInstance::set_mesh_rotation(const glm::vec3& rotation)
{
	object_location_.rotation = rotation;
}

void ScrapEngine::Render::VulkanMeshInstance::set_mesh_scale(const glm::vec3& scale)
{
	object_location_.scale = scale;
}

glm::vec3 ScrapEngine::Render::VulkanMeshInstance::get_mesh_location() const
{
	return object_location_.location;
}

glm::vec3 ScrapEngine::Render::VulkanMeshInstance::get_mesh_rotation() const
{
	return object_location_.rotation;
}

glm::vec3 ScrapEngine::Render::VulkanMeshInstance::get_mesh_scale() const
{
	return object_location_.scale;
}

void ScrapEngine::Render::VulkanMeshInstance::update_uniform_buffer(const uint32_t& current_image,
                                                                    ScrapEngine::Render::Camera* render_camera) const
{
	vulkan_render_uniform_buffer_->update_uniform_buffer(current_image, object_location_, render_camera);
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
