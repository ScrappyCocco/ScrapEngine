#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::VulkanSkyboxInstance::VulkanSkyboxInstance(const std::string& vertex_shader_path,
                                                                const std::string& fragment_shader_path,
                                                                const std::string& model_path,
                                                                const std::array<std::string, 6>& texture_path,
                                                                ScrapEngine::Render::VulkanDevice* render_device,
                                                                ScrapEngine::Render::VulkanSwapChain* swap_chain)
{
	//CREATE UNIFORM BUFFER
	vulkan_render_uniform_buffer_ = new UniformBuffer(swap_chain->get_swap_chain_images_vector(),
	                                                  swap_chain->get_swap_chain_extent());
	Debug::DebugLog::print_to_console_log("UniformBuffer created");
	//CREATE MATERIAL(S)
	skybox_material_ = new SkyboxMaterial();
	Debug::DebugLog::print_to_console_log("VulkanDescriptorSet created");
	skybox_material_->create_pipeline(vertex_shader_path,
	                                  fragment_shader_path, swap_chain, render_device);
	skybox_material_->create_skybox_texture(texture_path);
	skybox_material_->create_descriptor_sets(swap_chain, vulkan_render_uniform_buffer_);
	//LOADING 3D MODEL AND BUFFERS
	vulkan_render_model_ = new VulkanModel(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	if (vulkan_render_model_->get_meshes()->size() > 1)
	{
		throw std::runtime_error("Cannot use a cubemap with a model containing more than one mesh!");
	}
	created_vertex_buffer_ = new VertexBuffer((*vulkan_render_model_->get_meshes())[0]->get_vertices());
	Debug::DebugLog::print_to_console_log("VertexBuffer created");
	created_index_buffer_ = new IndexBuffer((*vulkan_render_model_->get_meshes())[0]->get_indices());
	Debug::DebugLog::print_to_console_log("IndexBuffer created");
	mesh_buffers_.first = new VertexBufferContainer(created_vertex_buffer_->get_vertex_buffer(),
	                                                (*vulkan_render_model_->get_meshes())[0]->get_vertices());
	mesh_buffers_.second = new IndicesBufferContainer(created_index_buffer_->get_index_buffer(),
	                                                  (*vulkan_render_model_->get_meshes())[0]->get_indices());
	skybox_transform_.location = glm::vec3(0, 0, 0);
	skybox_transform_.scale = glm::vec3(50, 50, 50);
}

ScrapEngine::Render::VulkanSkyboxInstance::~VulkanSkyboxInstance()
{
	delete mesh_buffers_.first;
	delete mesh_buffers_.second;
	delete skybox_material_;
	delete vulkan_render_uniform_buffer_;
	delete created_vertex_buffer_;
	delete created_index_buffer_;
	delete vulkan_render_model_;
}

void ScrapEngine::Render::VulkanSkyboxInstance::update_uniform_buffer(const uint32_t& current_image,
                                                                      ScrapEngine::Render::Camera* render_camera) const
{
	vulkan_render_uniform_buffer_->update_uniform_buffer(current_image, skybox_transform_, render_camera);
}

int ScrapEngine::Render::VulkanSkyboxInstance::get_cubemap_size() const
{
	return static_cast<int>(skybox_transform_.scale.x);
}

void ScrapEngine::Render::VulkanSkyboxInstance::set_cubemap_size(unsigned int new_size)
{
	skybox_transform_.scale = glm::vec3(new_size, new_size, new_size);
}

ScrapEngine::Render::UniformBuffer* ScrapEngine::Render::VulkanSkyboxInstance::get_vulkan_render_uniform_buffer() const
{
	return vulkan_render_uniform_buffer_;
}

ScrapEngine::Render::BasicMaterial* ScrapEngine::Render::VulkanSkyboxInstance::get_skybox_material() const
{
	return skybox_material_;
}

const std::pair<ScrapEngine::Render::VertexBufferContainer*, ScrapEngine::Render::IndicesBufferContainer*>* ScrapEngine
::
Render::VulkanSkyboxInstance::get_mesh_buffers() const
{
	return &mesh_buffers_;
}
