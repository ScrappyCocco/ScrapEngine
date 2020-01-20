#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

namespace ScrapEngine
{
	namespace Render
	{
		class DebugQuadPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			DebugQuadPipeline(const char* vertex_shader, const char* fragment_shader,
			                  vk::DescriptorSetLayout* descriptor_set_layout, vk::Extent2D* swap_chain_extent);
			~DebugQuadPipeline() = default;
		};
	}
}
