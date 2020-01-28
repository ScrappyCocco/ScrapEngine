#include <Engine/Rendering/Descriptor/DescriptorPool/GuiDescriptorPool/GuiDescriptorPool.h>
#include <array>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

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

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createDescriptorPool(&pool_info, nullptr, &descriptor_pool_);
	
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "GuiDescriptorPool: Failed to create descriptor pool!");
	}
}
