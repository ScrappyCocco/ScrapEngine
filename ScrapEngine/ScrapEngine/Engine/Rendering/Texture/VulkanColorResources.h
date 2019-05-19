#pragma once

#include <vulkan/vulkan.hpp>
#include "../SwapChain/VulkanSwapChain.h"

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanColorResources
		{
		private:
			vk::Image color_image_;
			vk::DeviceMemory color_image_memory_;
			vk::ImageView color_image_view_;
		public:
			VulkanColorResources(vk::SampleCountFlagBits msaa_samples,
			                     ScrapEngine::Render::VulkanSwapChain* swap_chain_ref);
			~VulkanColorResources();

			vk::Image* get_color_image();
			vk::ImageView* get_color_image_view();
		};
	}
}
