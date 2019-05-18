#include "VulkanDescriptorPool.h"
#include <array>
#include "../Base/StaticTypes.h"

ScrapEngine::Render::VulkanDescriptorPool::VulkanDescriptorPool(const std::vector<vk::Image>* swapChainImages)
{
	std::array<vk::DescriptorPoolSize, 2> poolSizes = {
		vk::DescriptorPoolSize(vk::DescriptorType::eUniformBuffer, static_cast<uint32_t>(swapChainImages->size())),
		vk::DescriptorPoolSize(vk::DescriptorType::eCombinedImageSampler, static_cast<uint32_t>(swapChainImages->size())),
	};

	vk::DescriptorPoolCreateInfo poolInfo(
		vk::DescriptorPoolCreateFlags(),
		static_cast<uint32_t>(swapChainImages->size()),
		static_cast<uint32_t>(poolSizes.size()), poolSizes.data()
	);

	if (VulkanDevice::StaticLogicDeviceRef->createDescriptorPool(&poolInfo, nullptr, &descriptorPool) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanDescriptorPool: Failed to create descriptor pool!");
	}
}

ScrapEngine::Render::VulkanDescriptorPool::~VulkanDescriptorPool()
{
	VulkanDevice::StaticLogicDeviceRef->destroyDescriptorPool(descriptorPool);
}

vk::DescriptorPool* ScrapEngine::Render::VulkanDescriptorPool::getDescriptorPool()
{
	return &descriptorPool;
}
