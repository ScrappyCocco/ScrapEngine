#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Base/StaticTypes.h>

ScrapEngine::Render::BaseVulkanGraphicsPipeline::~BaseVulkanGraphicsPipeline()
{
	VulkanDevice::static_logic_device_ref->destroyPipeline(graphics_pipeline_);
	VulkanDevice::static_logic_device_ref->destroyPipelineLayout(pipeline_layout_);
}

vk::Pipeline* ScrapEngine::Render::BaseVulkanGraphicsPipeline::get_graphics_pipeline()
{
	return &graphics_pipeline_;
}

vk::PipelineLayout* ScrapEngine::Render::BaseVulkanGraphicsPipeline::get_pipeline_layout()
{
	return &pipeline_layout_;
}
