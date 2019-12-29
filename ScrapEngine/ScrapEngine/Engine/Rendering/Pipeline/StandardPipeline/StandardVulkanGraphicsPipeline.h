#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardVulkanGraphicsPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			StandardVulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                               vk::Extent2D* swap_chain_extent,
			                               vk::DescriptorSetLayout* descriptor_set_layout,
			                               vk::SampleCountFlagBits msaa_samples);
			~StandardVulkanGraphicsPipeline() = default;
		};
	}
}
