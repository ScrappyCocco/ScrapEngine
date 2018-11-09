#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../Buffer/Uniform/UniformBuffer.h"

namespace ScrapEngine {

	class VulkanDescriptorSet
	{
	private:
		vk::DescriptorSetLayout descriptorSetLayout;
		vk::PipelineLayout pipelineLayout;
		std::vector<vk::DescriptorSet> descriptorSets;

		vk::Device* deviceRef;
	public:
		VulkanDescriptorSet(vk::Device* input_deviceRef);
		~VulkanDescriptorSet();

		void createDescriptorSets(vk::DescriptorPool* descriptorPool, const std::vector<vk::Image>* swapChainImages, const std::vector<vk::Buffer>* uniformBuffers, vk::ImageView* textureImageView, vk::Sampler* textureSampler, vk::DeviceSize BufferInfoSize = sizeof(UniformBufferObject));

		vk::DescriptorSetLayout* getDescriptorSetLayout();
		vk::PipelineLayout* getPipelineLayout();
		const std::vector<vk::DescriptorSet>* getDescriptorSets();
	};

}

