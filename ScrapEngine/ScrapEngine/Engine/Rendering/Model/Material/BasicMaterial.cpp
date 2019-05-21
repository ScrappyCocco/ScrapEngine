#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::BasicMaterial::BasicMaterial()
{
	vulkan_render_descriptor_set_ = new VulkanDescriptorSet();
	Debug::DebugLog::print_to_console_log("VulkanDescriptorSet created");
}

ScrapEngine::Render::BasicMaterial::~BasicMaterial()
{
	Debug::DebugLog::print_to_console_log("Delete BasicMaterial");
	delete_graphics_pipeline();
	delete vulkan_render_descriptor_set_;
	Debug::DebugLog::print_to_console_log("Delete BasicMaterial done");
}

void ScrapEngine::Render::BasicMaterial::delete_graphics_pipeline()
{
	Debug::DebugLog::print_to_console_log("---Delete pipeline");
	delete vulkan_render_graphics_pipeline_;
	vulkan_render_graphics_pipeline_ = nullptr;
}

ScrapEngine::Render::BaseVulkanGraphicsPipeline* ScrapEngine::Render::BasicMaterial::
get_vulkan_render_graphics_pipeline() const
{
	return vulkan_render_graphics_pipeline_;
}

ScrapEngine::Render::VulkanDescriptorSet* ScrapEngine::Render::BasicMaterial::get_vulkan_render_descriptor_set() const
{
	return vulkan_render_descriptor_set_;
}
