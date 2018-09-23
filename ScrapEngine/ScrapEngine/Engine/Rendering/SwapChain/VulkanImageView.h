#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

#include "VulkanSwapChain.h"

namespace ScrapEngine {

	class VulkanImageView
	{
	private:
		std::vector<vk::ImageView> swapChainImageViews;

		vk::Device* deviceRef;
	public:
		VulkanImageView(vk::Device* input_deviceRef, ScrapEngine::VulkanSwapChain* SwapChainRef);
		~VulkanImageView();

		const std::vector<vk::ImageView>* getSwapChainImageViewsVector();
	};

}

