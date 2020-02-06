#pragma once

#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseRenderPass;

		class ShadowmappingPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			ShadowmappingPipeline(const char* vertex_shader,
			                      vk::DescriptorSetLayout* descriptor_set_layout, vk::Extent2D* shadowmapping_extent,
			                      BaseRenderPass* render_pass);
			~ShadowmappingPipeline() = default;
		};
	}
}
