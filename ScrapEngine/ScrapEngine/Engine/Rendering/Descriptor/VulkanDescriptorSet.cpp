#include "VulkanDescriptorSet.h"

#include <stdexcept>
#include "../Buffer/Uniform/UniformBuffer.h"
#include <array>

ScrapEngine::VulkanDescriptorSet::VulkanDescriptorSet(VkDevice input_deviceRef) 
	: deviceRef(input_deviceRef)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(deviceRef, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

ScrapEngine::VulkanDescriptorSet::~VulkanDescriptorSet()
{
	vkDestroyDescriptorSetLayout(deviceRef, descriptorSetLayout, nullptr);
}

void ScrapEngine::VulkanDescriptorSet::createDescriptorSets(VkDescriptorPool descriptorPool, const std::vector<VkImage>* swapChainImages, const std::vector<VkBuffer>* uniformBuffers, VkImageView textureImageView, VkSampler textureSampler)
{
	std::vector<VkDescriptorSetLayout> layouts(swapChainImages->size(), descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages->size());
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(swapChainImages->size());
	if (vkAllocateDescriptorSets(deviceRef, &allocInfo, &descriptorSets[0]) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < swapChainImages->size(); i++) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = (*uniformBuffers)[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = textureImageView;
		imageInfo.sampler = textureSampler;

		std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = descriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = descriptorSets[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pImageInfo = &imageInfo;

		vkUpdateDescriptorSets(deviceRef, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}
}

VkDescriptorSetLayout ScrapEngine::VulkanDescriptorSet::getDescriptorSetLayout() const
{
	return descriptorSetLayout;
}

VkPipelineLayout ScrapEngine::VulkanDescriptorSet::getPipelineLayout() const
{
	return pipelineLayout;
}

const std::vector<VkDescriptorSet>* ScrapEngine::VulkanDescriptorSet::getDescriptorSets()
{
	return &descriptorSets;
}
