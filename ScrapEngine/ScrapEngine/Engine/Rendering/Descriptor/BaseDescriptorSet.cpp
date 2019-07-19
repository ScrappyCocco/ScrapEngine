#include <Engine/Rendering/Descriptor/BaseDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::BaseDescriptorSet::~BaseDescriptorSet()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyDescriptorSetLayout(descriptor_set_layout_);
}

vk::DescriptorSetLayout* ScrapEngine::Render::BaseDescriptorSet::get_descriptor_set_layout()
{
	return &descriptor_set_layout_;
}

vk::PipelineLayout* ScrapEngine::Render::BaseDescriptorSet::get_pipeline_layout()
{
	return &pipeline_layout_;
}

const std::vector<vk::DescriptorSet>* ScrapEngine::Render::BaseDescriptorSet::get_descriptor_sets() const
{
	return &descriptor_sets_;
}
