#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseVulkanGraphicsPipeline
		{
		protected:
			vk::PipelineLayout pipeline_layout_;
			vk::Pipeline graphics_pipeline_;
		public:
			BaseVulkanGraphicsPipeline() = default;
			virtual ~BaseVulkanGraphicsPipeline() = 0;

			vk::Pipeline* get_graphics_pipeline();
			vk::PipelineLayout* get_pipeline_layout();
		};
	}
}
