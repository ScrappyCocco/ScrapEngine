#pragma once

#include <vulkan/vulkan.hpp>
#include "../Shader/ShaderManager.h"

namespace ScrapEngine {

	class VulkanGraphicsPipeline
	{
	private:
		ShaderManager* ShaderManagerRef = nullptr;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline graphicsPipeline;

		vk::Device* deviceRef;
	public:
		VulkanGraphicsPipeline(const char* vertexShader, const char* fragmentShader, vk::Device* input_deviceRef, vk::Extent2D* swapChainExtent, vk::RenderPass* input_renderPassRef,
			vk::DescriptorSetLayout* descriptorSetLayout, vk::SampleCountFlagBits msaaSamples);
		~VulkanGraphicsPipeline();

		vk::Pipeline* getGraphicsPipeline();
		vk::PipelineLayout* getPipelineLayout();
	};

}

