#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace ScrapEngine {

	class VulkanDescriptorSet
	{
	private:
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
		std::vector<VkDescriptorSet> descriptorSets;

		VkDevice deviceRef;
	public:
		VulkanDescriptorSet(VkDevice input_deviceRef);
		~VulkanDescriptorSet();

		void createDescriptorSets(VkDescriptorPool descriptorPool, const std::vector<VkImage>* swapChainImages, const std::vector<VkBuffer>* uniformBuffers, VkImageView textureImageView, VkSampler textureSampler);

		VkDescriptorSetLayout getDescriptorSetLayout() const;
		VkPipelineLayout getPipelineLayout() const;
		const std::vector<VkDescriptorSet>* getDescriptorSets();
	};

}

