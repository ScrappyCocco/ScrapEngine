#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanDepthResources
		{
		private:
			vk::Image depth_image_;
			VmaAllocation depth_image_memory_;
			vk::ImageView depth_image_view_;
		public:
			VulkanDepthResources(const vk::Extent2D* swap_chain_extent, vk::SampleCountFlagBits msaa_samples);
			~VulkanDepthResources();

			static vk::Format find_supported_format(const std::vector<vk::Format>& candidates, vk::ImageTiling tiling,
			                                        const vk::FormatFeatureFlags& features);
			static vk::Format find_depth_format();
			static bool has_stencil_component(const vk::Format& format);

			vk::Image* get_depth_image();
			vk::ImageView* get_depth_image_view();
		};
	}
}
