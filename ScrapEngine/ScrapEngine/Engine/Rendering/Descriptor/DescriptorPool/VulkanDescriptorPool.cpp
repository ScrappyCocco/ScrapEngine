#include <Engine/Rendering/Descriptor/DescriptorPool/VulkanDescriptorPool.h>
#include <array>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::VulkanDescriptorPool::VulkanDescriptorPool(const std::vector<vk::Image>* swap_chain_images)
{
	std::array<vk::DescriptorPoolSize, 2> pool_sizes = {
		vk::DescriptorPoolSize(vk::DescriptorType::eUniformBuffer, static_cast<uint32_t>(swap_chain_images->size())),
		vk::DescriptorPoolSize(vk::DescriptorType::eCombinedImageSampler,
		                       static_cast<uint32_t>(swap_chain_images->size())),
	};

	vk::DescriptorPoolCreateInfo pool_info(
		vk::DescriptorPoolCreateFlags(),
		static_cast<uint32_t>(swap_chain_images->size()),
		static_cast<uint32_t>(pool_sizes.size()), pool_sizes.data()
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createDescriptorPool(&pool_info, nullptr, &descriptor_pool_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("VulkanDescriptorPool: Failed to create descriptor pool!");
	}
}

ScrapEngine::Render::VulkanDescriptorPool::~VulkanDescriptorPool()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyDescriptorPool(descriptor_pool_);
}

vk::DescriptorPool* ScrapEngine::Render::VulkanDescriptorPool::get_descriptor_pool()
{
	return &descriptor_pool_;
}
