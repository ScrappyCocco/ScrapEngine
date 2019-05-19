#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

#include "VulkanSwapChain.h"

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanImageView
		{
		private:
			std::vector<vk::ImageView> swap_chain_image_views_;
		public:
			VulkanImageView(ScrapEngine::Render::VulkanSwapChain* swap_chain_ref);
			~VulkanImageView();

			const std::vector<vk::ImageView>* get_swap_chain_image_views_vector() const;
		};
	}
}
