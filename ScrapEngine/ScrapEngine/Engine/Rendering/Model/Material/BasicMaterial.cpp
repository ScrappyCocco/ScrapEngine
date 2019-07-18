#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::BasicMaterial::BasicMaterial()
{
	vulkan_render_descriptor_set_ = new VulkanDescriptorSet();
}

ScrapEngine::Render::BasicMaterial::~BasicMaterial()
{
	delete_graphics_pipeline();
	delete vulkan_render_descriptor_set_;
}

void ScrapEngine::Render::BasicMaterial::delete_graphics_pipeline()
{
	vulkan_render_graphics_pipeline_ = nullptr;
}

std::shared_ptr<ScrapEngine::Render::BaseVulkanGraphicsPipeline> ScrapEngine::Render::BasicMaterial::
get_vulkan_render_graphics_pipeline() const
{
	return vulkan_render_graphics_pipeline_;
}

ScrapEngine::Render::VulkanDescriptorSet* ScrapEngine::Render::BasicMaterial::get_vulkan_render_descriptor_set() const
{
	return vulkan_render_descriptor_set_;
}
