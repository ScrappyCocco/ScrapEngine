#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>
#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GuiVulkanGraphicsPipeline : public BaseVulkanGraphicsPipeline
		{
		private:
			vk::PipelineCache pipeline_cache_;
		public:
			GuiVulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                       vk::Extent2D* swap_chain_extent,
			                       vk::DescriptorSetLayout* descriptor_set_layout, size_t block_size,
			                       BaseRenderPass* render_pass);
			~GuiVulkanGraphicsPipeline();

			vk::PipelineCache* get_pipeline_cache();
		};
	}
}
