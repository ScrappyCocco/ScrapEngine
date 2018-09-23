#pragma once

#include <vulkan/vulkan.hpp>
#include "../SwapChain/VulkanImageView.h"
#include <vector>

namespace ScrapEngine {

	class VulkanFrameBuffer
	{
	private:
		std::vector<vk::Framebuffer> swapChainFramebuffers;

		vk::Device* deviceRef;
	public:
		VulkanFrameBuffer(ScrapEngine::VulkanImageView* input_imageViewRef, vk::Device* input_deviceRef, const vk::Extent2D* input_swapChainExtent,
			vk::ImageView* depthImageView, vk::RenderPass* renderPass, vk::ImageView* colorImageView);
		~VulkanFrameBuffer();

		const std::vector<vk::Framebuffer>* getSwapChainFramebuffersVector();
		size_t getSwapChainFramebuffersVectorSize() const;
	};

}

