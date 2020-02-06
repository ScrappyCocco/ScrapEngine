#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSwapChain;

		class VulkanImageView
		{
		private:
			std::vector<vk::ImageView> swap_chain_image_views_;
		public:
			VulkanImageView(VulkanSwapChain* swap_chain_ref);
			~VulkanImageView();

			const std::vector<vk::ImageView>* get_swap_chain_image_views_vector() const;
		};
	}
}
