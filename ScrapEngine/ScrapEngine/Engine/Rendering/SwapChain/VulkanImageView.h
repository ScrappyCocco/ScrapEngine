#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

#include "VulkanSwapChain.h"

namespace ScrapEngine {
	namespace Render {
		class VulkanImageView
		{
		private:
			std::vector<vk::ImageView> swapChainImageViews;
		public:
			VulkanImageView(ScrapEngine::Render::VulkanSwapChain* SwapChainRef);
			~VulkanImageView();

			const std::vector<vk::ImageView>* getSwapChainImageViewsVector();
		};
	}
}

