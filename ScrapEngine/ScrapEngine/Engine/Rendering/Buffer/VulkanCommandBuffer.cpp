#include "VulkanCommandBuffer.h"

ScrapEngine::VulkanCommandBuffer::VulkanCommandBuffer(ScrapEngine::VulkanFrameBuffer* SwapChainFrameBuffer, VkDevice input_deviceRef, VkCommandPool input_commandPoolRef, VkRenderPass input_renderPassRef, VkExtent2D input_swapChainExtentRef, 
	const ScrapEngine::VulkanGraphicsPipeline* input_vulkanPipelineRef, const std::vector<VkDescriptorSet>* descriptorSets, simple_buffer<Vertex> vertexBuffer, simple_buffer<uint32_t> indexBuffer)
	: deviceRef(input_deviceRef)
{
	const std::vector<VkFramebuffer>* swapChainFramebuffers = SwapChainFrameBuffer->getSwapChainFramebuffersVector();
	commandBuffers.resize(swapChainFramebuffers->size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = input_commandPoolRef;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(input_deviceRef, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffers.size(); i++) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = input_renderPassRef;
		renderPassInfo.framebuffer = (*swapChainFramebuffers)[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = input_swapChainExtentRef;

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();


		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, input_vulkanPipelineRef->getGraphicsPipeline());

		VkBuffer vertexBuffers[] = { vertexBuffer.buffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

		vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer.buffer, 0, VK_INDEX_TYPE_UINT32);

		vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, input_vulkanPipelineRef->getPipelineLayout(), 0, 1, &(*descriptorSets)[i], 0, nullptr);

		vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indexBuffer.vectorData->size()), 1, 0, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}

ScrapEngine::VulkanCommandBuffer::~VulkanCommandBuffer()
{

}

const std::vector<VkCommandBuffer>* ScrapEngine::VulkanCommandBuffer::getCommandBuffersVector()
{
	return &commandBuffers;
}
