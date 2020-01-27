#include <Engine/Rendering/Model/Material/SimpleMaterial/SimpleMaterial.h>
#include <Engine/Rendering/Pipeline/StandardPipeline/StandardVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanSimpleMaterialPool/VulkanSimpleMaterialPool.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/StandardDescriptorPool/StandardDescriptorPool.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/StandardDescriptorSet/StandardDescriptorSet.h>

ScrapEngine::Render::SimpleMaterial::SimpleMaterial()
{
	vulkan_render_descriptor_set_ = new StandardDescriptorSet();
}

ScrapEngine::Render::SimpleMaterial::~SimpleMaterial()
{
	delete vulkan_render_descriptor_pool_;
}

void ScrapEngine::Render::SimpleMaterial::create_pipeline(const std::string& vertex_shader_path,
                                                          const std::string& fragment_shader_path,
                                                          VulkanSwapChain* swap_chain)
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

void ScrapEngine::Render::SimpleMaterial::create_descriptor_sets(VulkanSwapChain* swap_chain,
                                                                 StandardUniformBuffer* uniform_buffer)
{
	const size_t size = swap_chain->get_swap_chain_images_vector()->size();
	//A standard model has two images, one for the depth pass and one texture, so double the size of possible descriptors
	vulkan_render_descriptor_pool_ = new StandardDescriptorPool(size * 2);
	StandardDescriptorSet* standard_descriptor_set = static_cast<StandardDescriptorSet*>(vulkan_render_descriptor_set_);
	standard_descriptor_set->create_descriptor_sets(vulkan_render_descriptor_pool_->get_descriptor_pool(),
	                                                size,
	                                                uniform_buffer->get_uniform_buffers(),
	                                                vulkan_texture_image_view_->get_texture_image_view(),
	                                                vulkan_texture_sampler_->get_texture_sampler());
}
