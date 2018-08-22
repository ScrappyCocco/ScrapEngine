#pragma once

#include <vulkan/vulkan.h>
#include "../Shader/ShaderManager.h"

namespace ScrapEngine {

	class VulkanGraphicsPipeline
	{
	private:
		ShaderManager* ShaderManagerRef = nullptr;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkDevice deviceRef;
	public:
		VulkanGraphicsPipeline(const char* vertexShader, const char* fragmentShader, VkDevice input_deviceRef, VkExtent2D swapChainExtent, VkRenderPass input_renderPassRef, 
			VkDescriptorSetLayout descriptorSetLayout, VkSampleCountFlagBits msaaSamples);
		~VulkanGraphicsPipeline();

		VkPipeline getGraphicsPipeline() const;
		VkPipelineLayout getPipelineLayout() const;
	};

}

