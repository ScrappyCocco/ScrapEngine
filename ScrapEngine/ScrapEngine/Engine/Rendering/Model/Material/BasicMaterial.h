#pragma once

#include <Engine/Rendering/Pipeline/VulkanGraphicsPipeline.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorSet.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BasicMaterial
		{
		protected:
			ScrapEngine::Render::VulkanGraphicsPipeline* vulkan_render_graphics_pipeline_ = nullptr;
			ScrapEngine::Render::VulkanDescriptorSet* vulkan_render_descriptor_set_ = nullptr;
		public:
			BasicMaterial();
			virtual ~BasicMaterial() = 0;

			void delete_graphics_pipeline();

			ScrapEngine::Render::VulkanGraphicsPipeline* get_vulkan_render_graphics_pipeline() const;
			ScrapEngine::Render::VulkanDescriptorSet* get_vulkan_render_descriptor_set() const;
		};
	}
}
