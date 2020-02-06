#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSwapChain;

		class VulkanColorResources
		{
		private:
			vk::Image color_image_;
			VmaAllocation color_image_memory_;
			vk::ImageView color_image_view_;
		public:
			VulkanColorResources(vk::SampleCountFlagBits msaa_samples,
			                     VulkanSwapChain* swap_chain_ref);
			~VulkanColorResources();

			vk::Image* get_color_image();
			vk::ImageView* get_color_image_view();
		};
	}
}
