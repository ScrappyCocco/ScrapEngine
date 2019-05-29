#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::BaseVulkanGraphicsPipeline::~BaseVulkanGraphicsPipeline()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyPipeline(graphics_pipeline_);
	VulkanDevice::get_instance()->get_logical_device()->destroyPipelineLayout(pipeline_layout_);
}

vk::Pipeline* ScrapEngine::Render::BaseVulkanGraphicsPipeline::get_graphics_pipeline()
{
	return &graphics_pipeline_;
}

vk::PipelineLayout* ScrapEngine::Render::BaseVulkanGraphicsPipeline::get_pipeline_layout()
{
	return &pipeline_layout_;
}
