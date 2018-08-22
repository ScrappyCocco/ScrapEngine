#pragma once

#include <vulkan/vulkan.h>
#include "VulkanFrameBuffer.h"
#include <vector>
#include "../Base/Vertex.h"
#include "../Pipeline/VulkanGraphicsPipeline.h"

namespace ScrapEngine {

	class VulkanCommandBuffer
	{
	private:
		std::vector<VkCommandBuffer> commandBuffers;

		VkDevice deviceRef;
	public:
		VulkanCommandBuffer(ScrapEngine::VulkanFrameBuffer* SwapChainFrameBuffer, VkDevice input_deviceRef, VkCommandPool input_commandPoolRef, 
			VkRenderPass input_renderPassRef, VkExtent2D input_swapChainExtentRef, const ScrapEngine::VulkanGraphicsPipeline* input_vulkanPipelineRef,
			const std::vector<VkDescriptorSet>* descriptorSets, simple_buffer<Vertex> vertexBuffer, simple_buffer<uint32_t> indexBuffer);
		~VulkanCommandBuffer();

		const std::vector<VkCommandBuffer>* getCommandBuffersVector();
	};

}

