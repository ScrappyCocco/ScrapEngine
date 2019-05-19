#include <Engine/Rendering/Model/VulkanMeshInstance.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path,
                                                            const std::string& fragment_shader_path,
                                                            const std::string& model_path,
                                                            const std::string& texture_path,
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
	                                                              render_device->get_msaa_samples());
	Debug::DebugLog::print_to_console_log("VulkanGraphicsPipeline created");
	vulkan_texture_image_ = new TextureImage(texture_path);
	Debug::DebugLog::print_to_console_log("TextureImage created");
	vulkan_texture_image_view_ = new TextureImageView(vulkan_texture_image_->get_texture_image(),
	                                                  vulkan_texture_image_->get_mip_levels());
	Debug::DebugLog::print_to_console_log("TextureImageView created");
	vulkan_texture_sampler_ = new TextureSampler(vulkan_texture_image_->get_mip_levels());
	Debug::DebugLog::print_to_console_log("TextureSampler created");
	vulkan_render_model_ = new VulkanModel(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	vulkan_render_vertex_buffer_ = new VertexBuffer(vulkan_render_model_->get_vertices());
	Debug::DebugLog::print_to_console_log("VertexBuffer created");
	vulkan_render_index_buffer_ = new IndexBuffer(vulkan_render_model_->get_indices());
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
	vertexbuffer_ = new simple_buffer<Vertex>(vulkan_render_vertex_buffer_->get_vertex_buffer(),
	                                          vulkan_render_model_->get_vertices());
	indexbuffer_ = new simple_buffer<uint32_t>(vulkan_render_index_buffer_->get_index_buffer(),
	                                           vulkan_render_model_->get_indices());
}

ScrapEngine::Render::VulkanMeshInstance::~VulkanMeshInstance()
{
	delete vertexbuffer_;
	delete indexbuffer_;
	delete_graphics_pipeline();
	delete vulkan_texture_sampler_;
	delete vulkan_texture_image_view_;
	delete vulkan_texture_image_;
	delete vulkan_render_descriptor_pool_;
	delete vulkan_render_descriptor_set_;
	delete vulkan_render_uniform_buffer_;
	delete vulkan_render_index_buffer_;
	delete vulkan_render_vertex_buffer_;
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

ScrapEngine::Render::VulkanGraphicsPipeline* ScrapEngine::Render::VulkanMeshInstance::
get_vulkan_render_graphics_pipeline() const
{
	return vulkan_render_graphics_pipeline_;
}

ScrapEngine::Render::VulkanDescriptorSet* ScrapEngine::Render::VulkanMeshInstance::
get_vulkan_render_descriptor_set() const
{
	return vulkan_render_descriptor_set_;
}

ScrapEngine::simple_buffer<ScrapEngine::Vertex>* ScrapEngine::Render::VulkanMeshInstance::get_vertex_buffer() const
{
	return vertexbuffer_;
}

ScrapEngine::simple_buffer<uint32_t>* ScrapEngine::Render::VulkanMeshInstance::get_index_buffer() const
{
	return indexbuffer_;
}

void ScrapEngine::Render::VulkanMeshInstance::delete_graphics_pipeline()
{
	delete vulkan_render_graphics_pipeline_;
	vulkan_render_graphics_pipeline_ = nullptr;
}
