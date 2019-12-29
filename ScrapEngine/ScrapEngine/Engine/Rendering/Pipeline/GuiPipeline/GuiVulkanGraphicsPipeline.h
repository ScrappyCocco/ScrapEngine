#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>
#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
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
