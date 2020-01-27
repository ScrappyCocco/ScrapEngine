#include <Engine/Rendering/Descriptor/DescriptorPool/GuiDescriptorPool/GuiDescriptorPool.h>
#include <array>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::GuiDescriptorPool::GuiDescriptorPool(const size_t size)
{
	std::array<vk::DescriptorPoolSize, 1> pool_sizes = {
		vk::DescriptorPoolSize(vk::DescriptorType::eCombinedImageSampler,
		                       static_cast<uint32_t>(size))
	};

	vk::DescriptorPoolCreateInfo pool_info(
		vk::DescriptorPoolCreateFlags(),
		static_cast<uint32_t>(size),
		static_cast<uint32_t>(pool_sizes.size()), pool_sizes.data()
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createDescriptorPool(&pool_info, nullptr, &descriptor_pool_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("GuiDescriptorPool: Failed to create descriptor pool!");
	}
}
