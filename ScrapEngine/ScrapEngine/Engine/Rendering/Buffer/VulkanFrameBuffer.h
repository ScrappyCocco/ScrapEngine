#pragma once

#include <vulkan/vulkan.hpp>
#include "../SwapChain/VulkanImageView.h"
#include <vector>

namespace ScrapEngine {

	class VulkanFrameBuffer
	{
	private:
		std::vector<vk::Framebuffer> swapChainFramebuffers;
	public:
		VulkanFrameBuffer(ScrapEngine::VulkanImageView* input_imageViewRef, const vk::Extent2D* input_swapChainExtent,
			vk::ImageView* depthImageView, vk::ImageView* colorImageView);
		~VulkanFrameBuffer();

		const std::vector<vk::Framebuffer>* getSwapChainFramebuffersVector();
		size_t getSwapChainFramebuffersVectorSize() const;
	};

}

