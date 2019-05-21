#include <Engine/Rendering/Model/VulkanMeshInstance.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path,
                                                            const std::string& fragment_shader_path,
                                                            const std::string& model_path,
                                                            const std::vector<std::string>& textures_path,
                                                            ScrapEngine::Render::VulkanDevice* render_device,
                                                            ScrapEngine::Render::VulkanSwapChain* swap_chain)
{
	vulkan_render_uniform_buffer_ = new UniformBuffer(swap_chain->get_swap_chain_images_vector(),
		swap_chain->get_swap_chain_extent());
	Debug::DebugLog::print_to_console_log("UniformBuffer created");
	vulkan_render_model_ = new VulkanModel(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	if(vulkan_render_model_->get_meshes()->size() != textures_path.size() && textures_path.size() > 1)
	{
		throw std::runtime_error("The texture array must have size 1 or equal number of meshes!");
	}
	for(const auto& texture_path: textures_path)
	{
		BasicMaterial* material = new BasicMaterial();
		material->create_pipeline(vertex_shader_path, fragment_shader_path, swap_chain, render_device);
		material->create_texture(texture_path);
		material->create_descriptor_sets(swap_chain, vulkan_render_uniform_buffer_);
		model_materials_.push_back(material);
	}
	for (auto mesh : (*vulkan_render_model_->get_meshes()))
	{
		std::pair<VertexBufferContainer*, IndicesBufferContainer*> buffer_pair;
		VertexBuffer* vulkan_render_vertex_buffer = new VertexBuffer(mesh->get_vertices());
		created_vertex_buffers_.push_back(vulkan_render_vertex_buffer);
		buffer_pair.first = new VertexBufferContainer(vulkan_render_vertex_buffer->get_vertex_buffer(),
		                                              mesh->get_vertices());
		Debug::DebugLog::print_to_console_log("VertexBuffer created");

		IndexBuffer* vulkan_render_index_buffer = new IndexBuffer(mesh->get_indices());
		created_index_buffers_.push_back(vulkan_render_index_buffer);
		buffer_pair.second = new IndicesBufferContainer(vulkan_render_index_buffer->get_index_buffer(),
		                                                mesh->get_indices());
		Debug::DebugLog::print_to_console_log("IndexBuffer created");

		mesh_buffers_.push_back(buffer_pair);
	}
}

ScrapEngine::Render::VulkanMeshInstance::~VulkanMeshInstance()
{
	// Delete the buffers of every mesh
	for (auto mesh_buffers : mesh_buffers_)
	{
		delete mesh_buffers.first;
		delete mesh_buffers.second;
	}
	// Delete the textures
	for(auto material : model_materials_)
	{
		delete material;
	}
	// Delete the uniform buffer
	delete vulkan_render_uniform_buffer_;
	// Delete the basic buffers
	for (auto v_buffer : created_vertex_buffers_)
	{
		delete v_buffer;
	}
	for (auto i_buffer : created_index_buffers_)
	{
		delete i_buffer;
	}
	// Delete the 3d model
	delete vulkan_render_model_;
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

const std::vector<std::pair<ScrapEngine::Render::VertexBufferContainer*, ScrapEngine::Render::IndicesBufferContainer*>>*
ScrapEngine::Render::VulkanMeshInstance::get_mesh_buffers() const
{
	return &mesh_buffers_;
}
