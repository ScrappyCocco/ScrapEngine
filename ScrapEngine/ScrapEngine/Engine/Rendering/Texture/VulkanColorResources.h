#pragma once

#include <vulkan/vulkan.hpp>
#include "../SwapChain/VulkanSwapChain.h"

namespace ScrapEngine{

	class VulkanColorResources
	{
	private:
		vk::Image colorImage;
		vk::DeviceMemory colorImageMemory;
		vk::ImageView colorImageView;
	public:
		VulkanColorResources(vk::SampleCountFlagBits msaaSamples, ScrapEngine::VulkanSwapChain* swapChainRef);
		~VulkanColorResources();

		vk::Image* getColorImage();
		vk::ImageView* getColorImageView();
	};

}
