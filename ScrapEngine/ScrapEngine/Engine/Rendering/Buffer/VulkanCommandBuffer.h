#pragma once

#include <vulkan/vulkan.hpp>
#include "VulkanFrameBuffer.h"
#include <vector>
#include "../Base/Vertex.h"
#include "../Pipeline/VulkanGraphicsPipeline.h"

namespace ScrapEngine {

	class VulkanCommandBuffer
	{
	private:
		std::vector<vk::CommandBuffer> commandBuffers;

		vk::Device* deviceRef;
	public:
		VulkanCommandBuffer(ScrapEngine::VulkanFrameBuffer* SwapChainFrameBuffer, vk::Device* input_deviceRef, vk::CommandPool* input_commandPoolRef, 
			vk::RenderPass* input_renderPassRef, vk::Extent2D* input_swapChainExtentRef, ScrapEngine::VulkanGraphicsPipeline* input_vulkanPipelineRef,
			const std::vector<vk::DescriptorSet>* descriptorSets, simple_buffer<Vertex> vertexBuffer, simple_buffer<uint32_t> indexBuffer);

		VulkanCommandBuffer(ScrapEngine::VulkanFrameBuffer* SwapChainFrameBuffer, vk::Device* input_deviceRef, vk::CommandPool* input_commandPoolRef,
			vk::RenderPass* input_renderPassRef, vk::Extent2D* input_swapChainExtentRef, std::vector<ScrapEngine::VulkanGraphicsPipeline*> input_vulkanPipelineRef,
			const std::vector<const std::vector<vk::DescriptorSet>*> descriptorSets, std::vector<simple_buffer<Vertex>*> vertexBuffer, std::vector<simple_buffer<uint32_t>*> indexBuffer);

		~VulkanCommandBuffer();

		const std::vector<vk::CommandBuffer>* getCommandBuffersVector();
	};

}

