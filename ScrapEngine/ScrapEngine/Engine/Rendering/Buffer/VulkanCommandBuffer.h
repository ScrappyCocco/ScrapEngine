#pragma once

#include <vulkan/vulkan.hpp>
#include "VulkanFrameBuffer.h"
#include <vector>
#include "../Base/Vertex.h"
#include "../Pipeline/VulkanGraphicsPipeline.h"
#include "../Model/VulkanSkyboxInstance.h"

namespace ScrapEngine {
	class VulkanSkyboxInstance;

	class VulkanCommandBuffer
	{
	private:
		std::vector<vk::CommandBuffer> commandBuffers;
	public:

		VulkanCommandBuffer(ScrapEngine::VulkanFrameBuffer* SwapChainFrameBuffer, vk::Extent2D* input_swapChainExtentRef, std::vector<ScrapEngine::VulkanGraphicsPipeline*> input_vulkanPipelineRef,
			const std::vector<const std::vector<vk::DescriptorSet>*>& descriptorSets, std::vector<simple_buffer<Vertex>*> vertexBuffer, std::vector<simple_buffer<uint32_t>*> indexBuffer
		, ScrapEngine::VulkanSkyboxInstance* SkyboxRef = nullptr);

		~VulkanCommandBuffer();

		void freeCommandBuffers();

		const std::vector<vk::CommandBuffer>* getCommandBuffersVector();
	};

}

