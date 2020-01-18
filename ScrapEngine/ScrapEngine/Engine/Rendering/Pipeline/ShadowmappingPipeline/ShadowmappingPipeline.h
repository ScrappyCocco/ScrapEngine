#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>
#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
		class ShadowmappingPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			ShadowmappingPipeline(const char* vertex_shader,
			                      vk::PipelineLayout* offscreen_layout, vk::Extent2D* swap_chain_extent,
			                      BaseRenderPass* render_pass);
			~ShadowmappingPipeline() = default;
		};
	}
}
