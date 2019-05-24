#include <Engine/Rendering/Model/Material/SimpleMaterial/SimpleMaterial.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Pipeline/StandardPipeline/StandardVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanSimpleMaterialPool/VulkanSimpleMaterialPool.h>

ScrapEngine::Render::SimpleMaterial::~SimpleMaterial()
{
	delete vulkan_render_descriptor_pool_;
}

void ScrapEngine::Render::SimpleMaterial::create_pipeline(const std::string& vertex_shader_path,
                                                          const std::string& fragment_shader_path,
                                                          ScrapEngine::Render::VulkanSwapChain* swap_chain)
{
	vulkan_render_graphics_pipeline_ = VulkanSimpleMaterialPool::get_instance()->get_pipeline(
		vertex_shader_path,
		fragment_shader_path,
		swap_chain,
		vulkan_render_descriptor_set_->get_descriptor_set_layout());
}

void ScrapEngine::Render::SimpleMaterial::create_texture(const std::string& texture_path)
{
	vulkan_texture_image_ = VulkanSimpleMaterialPool::get_instance()->get_standard_texture(texture_path);
	vulkan_texture_image_view_ = VulkanSimpleMaterialPool::get_instance()->get_texture_image_view(texture_path);
	vulkan_texture_sampler_ = VulkanSimpleMaterialPool::get_instance()->get_texture_sampler(texture_path);
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
