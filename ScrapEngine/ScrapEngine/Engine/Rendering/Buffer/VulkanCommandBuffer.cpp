#include "VulkanCommandBuffer.h"
#include "../../Debug/DebugLog.h"
#include "../Base/StaticTypes.h"

ScrapEngine::VulkanCommandBuffer::VulkanCommandBuffer(ScrapEngine::VulkanFrameBuffer* SwapChainFrameBuffer, vk::Extent2D* input_swapChainExtentRef, std::vector<ScrapEngine::VulkanGraphicsPipeline*> input_vulkanPipelineRef,
	const std::vector<const std::vector<vk::DescriptorSet>*> descriptorSets, std::vector<simple_buffer<Vertex>*> vertexBuffer, std::vector<simple_buffer<uint32_t>*> indexBuffer
	, ScrapEngine::VulkanSkyboxInstance* SkyboxRef)
{
	const std::vector<vk::Framebuffer>* swapChainFramebuffers = SwapChainFrameBuffer->getSwapChainFramebuffersVector();
	commandBuffers.resize(swapChainFramebuffers->size());

	vk::CommandBufferAllocateInfo allocInfo(
		*VulkanCommandPool::StaticCommandPoolRef, 
		vk::CommandBufferLevel::ePrimary, 
		(uint32_t)commandBuffers.size()
	);

	if (VulkanDevice::StaticLogicDeviceRef->allocateCommandBuffers(&allocInfo, commandBuffers.data()) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanCommandBuffer: Failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffers.size(); i++) {
		vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

		if (commandBuffers[i].begin(&beginInfo) != vk::Result::eSuccess) {
			throw std::runtime_error("VulkanCommandBuffer: Failed to begin recording command buffer!");
		}

		vk::RenderPassBeginInfo renderPassInfo(
			*VulkanRenderPass::StaticRenderPassRef, 
			(*swapChainFramebuffers)[i], 
			vk::Rect2D(vk::Offset2D(), *input_swapChainExtentRef)
		);

		std::array<vk::ClearValue, 2> clearValues = {
			vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{ 0.0f, 0.0f, 0.0f, 1.0f })),
			vk::ClearDepthStencilValue(1.0f, 0)
		};
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		commandBuffers[i].beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

		vk::DeviceSize offsets[] = { 0 };

		//Skybox render, must be before the rest of the render
		if (SkyboxRef) {
			commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, *SkyboxRef->getVulkanRenderGraphicsPipeline()->getGraphicsPipeline());
			vk::Buffer buff[] = { *SkyboxRef->getVertexbuffer()->buffer };
			commandBuffers[i].bindVertexBuffers(0, 1, buff, offsets);
			commandBuffers[i].bindIndexBuffer(*SkyboxRef->getIndexbuffer()->buffer, 0, vk::IndexType::eUint32);
			commandBuffers[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *SkyboxRef->getVulkanRenderGraphicsPipeline()->getPipelineLayout(), 0, 1, &(*SkyboxRef->getVulkanRenderDescriptorSet()->getDescriptorSets())[i], 0, nullptr);
			commandBuffers[i].drawIndexed(static_cast<uint32_t>((*SkyboxRef->getIndexbuffer()).vectorData->size()), 1, 0, 0, 0);
		}
		//Scene render
		for (int k = 0; k < vertexBuffer.size(); k++) {
			commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, *input_vulkanPipelineRef[k]->getGraphicsPipeline());

			vk::Buffer vertexBuffers[] = { *(*vertexBuffer[k]).buffer };

			commandBuffers[i].bindVertexBuffers(0, 1, vertexBuffers, offsets);

			commandBuffers[i].bindIndexBuffer(*(*indexBuffer[k]).buffer, 0, vk::IndexType::eUint32);

			commandBuffers[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *input_vulkanPipelineRef[k]->getPipelineLayout(), 0, 1, &(*descriptorSets[k])[i], 0, nullptr);

			commandBuffers[i].drawIndexed(static_cast<uint32_t>((*indexBuffer[k]).vectorData->size()), 1, 0, 0, 0);
		}

		commandBuffers[i].endRenderPass();

		commandBuffers[i].end();
	}
}

ScrapEngine::VulkanCommandBuffer::~VulkanCommandBuffer()
{

}

void ScrapEngine::VulkanCommandBuffer::freeCommandBuffers()
{
	VulkanDevice::StaticLogicDeviceRef->freeCommandBuffers(*VulkanCommandPool::StaticCommandPoolRef, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

}

const std::vector<vk::CommandBuffer>* ScrapEngine::VulkanCommandBuffer::getCommandBuffersVector()
{
	return &commandBuffers;
}
