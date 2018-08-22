#pragma once

#include <vulkan/vulkan.h>
#include "../SwapChain/VulkanImageView.h"
#include <vector>

namespace ScrapEngine {

	class VulkanFrameBuffer
	{
	private:
		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkDevice deviceRef;
	public:
		VulkanFrameBuffer(ScrapEngine::VulkanImageView* input_imageViewRef, VkRenderPass input_renderPassRef, VkDevice input_deviceRef, const VkExtent2D* input_swapChainExtent,
			VkImageView depthImageView, VkRenderPass renderPass, VkImageView colorImageView);
		~VulkanFrameBuffer();

		const std::vector<VkFramebuffer>* getSwapChainFramebuffersVector();
		size_t getSwapChainFramebuffersVectorSize() const;
	};

}

