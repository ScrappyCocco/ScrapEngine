#include <Engine/Rendering/Model/Material/SimpleMaterial/SimpleMaterial.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Pipeline/StandardPipeline/StandardVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Texture/Texture/StandardTexture/StandardTexture.h>

ScrapEngine::Render::SimpleMaterial::~SimpleMaterial()
{
	delete vulkan_texture_sampler_;
	delete vulkan_texture_image_view_;
	delete vulkan_texture_image_;
	delete vulkan_render_descriptor_pool_;
}

void ScrapEngine::Render::SimpleMaterial::create_pipeline(const std::string& vertex_shader_path,
                                                          const std::string& fragment_shader_path,
                                                          ScrapEngine::Render::VulkanSwapChain* swap_chain,
                                                          ScrapEngine::Render::VulkanDevice* render_device)
{
	vulkan_render_graphics_pipeline_ = new StandardVulkanGraphicsPipeline(vertex_shader_path.c_str(),
	                                                                      fragment_shader_path.c_str(),
	                                                                      &swap_chain->get_swap_chain_extent(),
	                                                                      vulkan_render_descriptor_set_->
	                                                                      get_descriptor_set_layout(),
	                                                                      render_device->get_msaa_samples());
	Debug::DebugLog::print_to_console_log("VulkanGraphicsPipeline created");
}

void ScrapEngine::Render::SimpleMaterial::create_texture(const std::string& texture_path)
{
	vulkan_texture_image_ = new StandardTexture(texture_path);
	Debug::DebugLog::print_to_console_log("TextureImage created");
	vulkan_texture_image_view_ = new TextureImageView(vulkan_texture_image_->get_texture_image(),
	                                                  vulkan_texture_image_->get_mip_levels());
	Debug::DebugLog::print_to_console_log("TextureImageView created");
	vulkan_texture_sampler_ = new TextureSampler(vulkan_texture_image_->get_mip_levels());
	Debug::DebugLog::print_to_console_log("TextureSampler created");
}

void ScrapEngine::Render::SimpleMaterial::create_descriptor_sets(ScrapEngine::Render::VulkanSwapChain* swap_chain,
                                                                 ScrapEngine::Render::UniformBuffer* uniform_buffer)
{
	vulkan_render_descriptor_pool_ = new VulkanDescriptorPool(swap_chain->get_swap_chain_images_vector());
	Debug::DebugLog::print_to_console_log("VulkanDescriptorPool created");
	vulkan_render_descriptor_set_->create_descriptor_sets(vulkan_render_descriptor_pool_->get_descriptor_pool(),
	                                                      swap_chain->get_swap_chain_images_vector(),
	                                                      uniform_buffer->get_uniform_buffers(),
	                                                      vulkan_texture_image_view_->get_texture_image_view(),
	                                                      vulkan_texture_sampler_->get_texture_sampler());
	Debug::DebugLog::print_to_console_log("(DescriptorSets created)");
}
