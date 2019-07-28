#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::BaseDescriptorPool::~BaseDescriptorPool()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyDescriptorPool(descriptor_pool_);
}

vk::DescriptorPool* ScrapEngine::Render::BaseDescriptorPool::get_descriptor_pool()
{
	return &descriptor_pool_;
}
