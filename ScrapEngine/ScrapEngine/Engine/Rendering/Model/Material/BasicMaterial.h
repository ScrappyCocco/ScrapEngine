#pragma once

#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseDescriptorSet;

		class BasicMaterial
		{
		protected:
			std::shared_ptr<BaseVulkanGraphicsPipeline> vulkan_render_graphics_pipeline_ = nullptr;
			BaseDescriptorSet* vulkan_render_descriptor_set_ = nullptr;
		public:
			BasicMaterial() = default;
			virtual ~BasicMaterial() = 0;

			void delete_graphics_pipeline();

			std::shared_ptr<BaseVulkanGraphicsPipeline> get_vulkan_render_graphics_pipeline() const;

			BaseDescriptorSet* get_vulkan_render_descriptor_set() const;
		};
	}
}
