#include "VulkanFrameBuffer.h"
#include <array>

ScrapEngine::VulkanFrameBuffer::VulkanFrameBuffer(ScrapEngine::VulkanImageView* input_imageViewRef, VkRenderPass input_renderPassRef, VkDevice input_deviceRef, const VkExtent2D* input_swapChainExtent, 
	VkImageView depthImageView, VkRenderPass renderPass, VkImageView colorImageView)
	: deviceRef(input_deviceRef)
{
	const std::vector<VkImageView>* swapChainImageViews = input_imageViewRef->getSwapChainImageViewsVector();

	swapChainFramebuffers.resize(swapChainImageViews->size());

	for (size_t i = 0; i < swapChainImageViews->size(); i++) {
		std::array<VkImageView, 3> attachments = {
			colorImageView,
			depthImageView,
			(*swapChainImageViews)[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = input_swapChainExtent->width;
		framebufferInfo.height = input_swapChainExtent->height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(deviceRef, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}

ScrapEngine::VulkanFrameBuffer::~VulkanFrameBuffer()
{
	for (auto framebuffer : swapChainFramebuffers) {
		vkDestroyFramebuffer(deviceRef, framebuffer, nullptr);
	}
}

const std::vector<VkFramebuffer>* ScrapEngine::VulkanFrameBuffer::getSwapChainFramebuffersVector()
{
	return &swapChainFramebuffers;
}

size_t ScrapEngine::VulkanFrameBuffer::getSwapChainFramebuffersVectorSize() const
{
	return swapChainFramebuffers.size();
}
