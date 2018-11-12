#include "VulkanFrameBuffer.h"
#include <array>
#include "../Base/StaticTypes.h"

ScrapEngine::VulkanFrameBuffer::VulkanFrameBuffer(ScrapEngine::VulkanImageView* input_imageViewRef, const vk::Extent2D* input_swapChainExtent,
	vk::ImageView* depthImageView, vk::ImageView* colorImageView)
{
	const std::vector<vk::ImageView>* swapChainImageViews = input_imageViewRef->getSwapChainImageViewsVector();

	swapChainFramebuffers.resize(swapChainImageViews->size());

	for (size_t i = 0; i < swapChainImageViews->size(); i++) {
		std::array<vk::ImageView, 3> attachments = {
			*colorImageView,
			*depthImageView,
			(*swapChainImageViews)[i]
		};

		vk::FramebufferCreateInfo framebufferInfo(
			vk::FramebufferCreateFlags(), 
			*VulkanRenderPass::StaticRenderPassRef, 
			static_cast<uint32_t>(attachments.size()), 
			attachments.data(), 
			input_swapChainExtent->width, 
			input_swapChainExtent->height, 
			1
		);
		
		if (VulkanDevice::StaticLogicDeviceRef->createFramebuffer(&framebufferInfo, nullptr, &swapChainFramebuffers[i]) != vk::Result::eSuccess) {
			throw std::runtime_error("VulkanFrameBuffer: Failed to create framebuffer!");
		}
	}
}

ScrapEngine::VulkanFrameBuffer::~VulkanFrameBuffer()
{
	for (auto framebuffer : swapChainFramebuffers) {
		VulkanDevice::StaticLogicDeviceRef->destroyFramebuffer(framebuffer);
	}
}

const std::vector<vk::Framebuffer>* ScrapEngine::VulkanFrameBuffer::getSwapChainFramebuffersVector()
{
	return &swapChainFramebuffers;
}

size_t ScrapEngine::VulkanFrameBuffer::getSwapChainFramebuffersVectorSize() const
{
	return swapChainFramebuffers.size();
}
