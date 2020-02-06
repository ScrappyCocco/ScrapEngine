#pragma once

#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseRenderPass;

		class GuiVulkanGraphicsPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			GuiVulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                          vk::DescriptorSetLayout* descriptor_set_layout, size_t block_size,
			                          BaseRenderPass* render_pass);
			~GuiVulkanGraphicsPipeline() = default;
		};
	}
}
