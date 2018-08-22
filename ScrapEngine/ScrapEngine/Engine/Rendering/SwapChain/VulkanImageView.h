#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanSwapChain.h"

namespace ScrapEngine {

	class VulkanImageView
	{
	private:
		std::vector<VkImageView> swapChainImageViews;

		VkDevice deviceRef;
	public:
		VulkanImageView(VkDevice input_deviceRef, ScrapEngine::VulkanSwapChain* SwapChainRef);
		~VulkanImageView();

		const std::vector<VkImageView>* getSwapChainImageViewsVector();
	};

}

