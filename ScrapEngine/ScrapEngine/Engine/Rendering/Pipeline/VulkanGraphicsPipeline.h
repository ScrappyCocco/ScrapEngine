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
	public:
		VulkanGraphicsPipeline(const char* vertexShader, const char* fragmentShader, vk::Extent2D* swapChainExtent,
			vk::DescriptorSetLayout* descriptorSetLayout, vk::SampleCountFlagBits msaaSamples, bool isSkybox = false);
		~VulkanGraphicsPipeline();

		vk::Pipeline* getGraphicsPipeline();
		vk::PipelineLayout* getPipelineLayout();
	};

}

