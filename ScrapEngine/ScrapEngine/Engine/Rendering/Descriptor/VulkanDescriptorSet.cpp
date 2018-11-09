#include "VulkanDescriptorSet.h"
#include <stdexcept>
#include <array>

ScrapEngine::VulkanDescriptorSet::VulkanDescriptorSet(vk::Device* input_deviceRef)
	: deviceRef(input_deviceRef)
{
	vk::DescriptorSetLayoutBinding uboLayoutBinding(
		0, 
		vk::DescriptorType::eUniformBuffer, 
		1,
		vk::ShaderStageFlagBits::eVertex, 
		nullptr
	);

	vk::DescriptorSetLayoutBinding samplerLayoutBinding(
		1,
		vk::DescriptorType::eCombinedImageSampler,
		1,
		vk::ShaderStageFlagBits::eFragment,
		nullptr
	);

	std::array<vk::DescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };

	vk::DescriptorSetLayoutCreateInfo layoutInfo(
		vk::DescriptorSetLayoutCreateFlags(), 
		static_cast<uint32_t>(bindings.size()), 
		bindings.data()
	);

	if (deviceRef->createDescriptorSetLayout(&layoutInfo, nullptr, &descriptorSetLayout) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanDescriptorSet: Failed to create descriptor set layout!");
	}
}

ScrapEngine::VulkanDescriptorSet::~VulkanDescriptorSet()
{
	deviceRef->destroyDescriptorSetLayout(descriptorSetLayout);
}

void ScrapEngine::VulkanDescriptorSet::createDescriptorSets(vk::DescriptorPool* descriptorPool, const std::vector<vk::Image>* swapChainImages, const std::vector<vk::Buffer>* uniformBuffers, vk::ImageView* textureImageView, vk::Sampler* textureSampler, vk::DeviceSize BufferInfoSize)
{
	std::vector<vk::DescriptorSetLayout> layouts(swapChainImages->size(), descriptorSetLayout);

	vk::DescriptorSetAllocateInfo allocInfo(
		*descriptorPool, 
		static_cast<uint32_t>(swapChainImages->size()), 
		layouts.data());

	descriptorSets.resize(swapChainImages->size());
	
	if (deviceRef->allocateDescriptorSets(&allocInfo, &descriptorSets[0]) != vk::Result::eSuccess) {
		throw std::runtime_error("DescriptorSetLayout: Failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < swapChainImages->size(); i++) {
		vk::DescriptorBufferInfo bufferInfo(
			(*uniformBuffers)[i], 
			0, 
			BufferInfoSize
		);

		vk::DescriptorImageInfo imageInfo(
			*textureSampler, 
			*textureImageView, 
			vk::ImageLayout::eShaderReadOnlyOptimal
		);

		std::array<vk::WriteDescriptorSet, 2> descriptorWrites = {
			vk::WriteDescriptorSet(
				descriptorSets[i], 
				0,
				0, 
				1, 
				vk::DescriptorType::eUniformBuffer, 
				nullptr, 
				&bufferInfo
			),
			vk::WriteDescriptorSet(
				descriptorSets[i], 
				1, 
				0, 
				1, 
				vk::DescriptorType::eCombinedImageSampler, 
				&imageInfo
			)
		};

		deviceRef->updateDescriptorSets(static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}
}

vk::DescriptorSetLayout* ScrapEngine::VulkanDescriptorSet::getDescriptorSetLayout()
{
	return &descriptorSetLayout;
}

vk::PipelineLayout* ScrapEngine::VulkanDescriptorSet::getPipelineLayout()
{
	return &pipelineLayout;
}

const std::vector<vk::DescriptorSet>* ScrapEngine::VulkanDescriptorSet::getDescriptorSets()
{
	return &descriptorSets;
}
