#include <Engine/Rendering/Model/VulkanSkyboxInstance.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::VulkanSkyboxInstance::VulkanSkyboxInstance(const std::string& vertex_shader_path,
                                                                const std::string& fragment_shader_path,
                                                                const std::string& model_path,
                                                                const std::array<std::string, 6>& texture_path,
                                                                ScrapEngine::Render::VulkanDevice* render_device,
                                                                ScrapEngine::Render::VulkanSwapChain* swap_chain)
{
	vulkan_render_descriptor_set_ = new VulkanDescriptorSet();
	Debug::DebugLog::print_to_console_log("VulkanDescriptorSet created");
	vulkan_render_graphics_pipeline_ = new VulkanGraphicsPipeline(vertex_shader_path.c_str(),
	                                                              fragment_shader_path.c_str(),
	                                                              &swap_chain->get_swap_chain_extent(),
	                                                              vulkan_render_descriptor_set_->
	                                                              get_descriptor_set_layout(),
	                                                              render_device->get_msaa_samples(), true);
	Debug::DebugLog::print_to_console_log("VulkanGraphicsPipeline created");
	skybox_texture_ = new ScrapEngine::Render::SkyboxTexture(texture_path);
	Debug::DebugLog::print_to_console_log("TextureImage created");
	vulkan_texture_image_view_ = new TextureImageView(skybox_texture_->get_texture_image(),
	                                                  skybox_texture_->get_mip_levels(), true, 6);
	Debug::DebugLog::print_to_console_log("TextureImageView created");
	vulkan_texture_sampler_ = new TextureSampler(skybox_texture_->get_mip_levels(), vk::Filter::eLinear,
	                                             vk::Filter::eLinear, vk::SamplerMipmapMode::eLinear,
	                                             vk::SamplerAddressMode::eClampToEdge,
	                                             vk::SamplerAddressMode::eClampToEdge,
	                                             vk::SamplerAddressMode::eClampToEdge,
	                                             false, vk::CompareOp::eNever, true, 16,
	                                             vk::BorderColor::eFloatOpaqueWhite);
	vulkan_render_model_ = new VulkanModel(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	if(vulkan_render_model_->get_meshes()->size() > 1)
	{
		throw "Cannot use a cubemap with a model containing more than one mesh!";
	}
	created_vertex_buffer_ = new VertexBuffer((*vulkan_render_model_->get_meshes())[0]->get_vertices());
	Debug::DebugLog::print_to_console_log("VertexBuffer created");
	created_index_buffer_ = new IndexBuffer((*vulkan_render_model_->get_meshes())[0]->get_indices());
	Debug::DebugLog::print_to_console_log("IndexBuffer created");
	vulkan_render_uniform_buffer_ = new UniformBuffer(swap_chain->get_swap_chain_images_vector(),
	                                                  swap_chain->get_swap_chain_extent());
	Debug::DebugLog::print_to_console_log("UniformBuffer created");
	vulkan_render_descriptor_pool_ = new VulkanDescriptorPool(swap_chain->get_swap_chain_images_vector());
	Debug::DebugLog::print_to_console_log("VulkanDescriptorPool created");
	vulkan_render_descriptor_set_->create_descriptor_sets(vulkan_render_descriptor_pool_->get_descriptor_pool(),
	                                                      swap_chain->get_swap_chain_images_vector(),
	                                                      vulkan_render_uniform_buffer_->get_uniform_buffers(),
	                                                      vulkan_texture_image_view_->get_texture_image_view(),
	                                                      vulkan_texture_sampler_->get_texture_sampler());
	Debug::DebugLog::print_to_console_log("(DescriptorSets created)");
	mesh_buffers_.first = new VertexBufferContainer(created_vertex_buffer_->get_vertex_buffer(), (*vulkan_render_model_->get_meshes())[0]->get_vertices());
	mesh_buffers_.second = new IndicesBufferContainer(created_index_buffer_->get_index_buffer(), (*vulkan_render_model_->get_meshes())[0]->get_indices());
	skybox_transform_.location = glm::vec3(0, 0, 0);
	skybox_transform_.scale = glm::vec3(50, 50, 50);
}

ScrapEngine::Render::VulkanSkyboxInstance::~VulkanSkyboxInstance()
{
	delete mesh_buffers_.first;
	delete mesh_buffers_.second;
	delete_graphics_pipeline();
	delete vulkan_texture_sampler_;
	delete vulkan_texture_image_view_;
	delete skybox_texture_;
	delete vulkan_render_descriptor_pool_;
	delete vulkan_render_descriptor_set_;
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

void ScrapEngine::Render::VulkanSkyboxInstance::delete_graphics_pipeline() const
{
	delete vulkan_render_graphics_pipeline_;
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

ScrapEngine::Render::VulkanGraphicsPipeline* ScrapEngine::Render::VulkanSkyboxInstance::
get_vulkan_render_graphics_pipeline() const
{
	return vulkan_render_graphics_pipeline_;
}

ScrapEngine::Render::VulkanDescriptorSet* ScrapEngine::Render::VulkanSkyboxInstance::
get_vulkan_render_descriptor_set() const
{
	return vulkan_render_descriptor_set_;
}

const std::pair<ScrapEngine::Render::VertexBufferContainer*, ScrapEngine::Render::IndicesBufferContainer*>* ScrapEngine::
Render::VulkanSkyboxInstance::get_mesh_buffers() const
{
	return &mesh_buffers_;
}
