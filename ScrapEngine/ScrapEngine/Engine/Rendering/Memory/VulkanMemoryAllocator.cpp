#define VMA_IMPLEMENTATION

#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

//Init static instance reference

ScrapEngine::Render::VulkanMemoryAllocator* ScrapEngine::Render::VulkanMemoryAllocator::instance_ = nullptr;

//Class

void ScrapEngine::Render::VulkanMemoryAllocator::init(const vk::PhysicalDevice physical_device, const vk::Device logical_device)
{
	VmaAllocatorCreateInfo allocator_info = {};
	allocator_info.physicalDevice = physical_device;
	allocator_info.device = logical_device;

	vmaCreateAllocator(&allocator_info, &allocator_);
}

ScrapEngine::Render::VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
	vmaDestroyAllocator(allocator_);
}

ScrapEngine::Render::VulkanMemoryAllocator* ScrapEngine::Render::VulkanMemoryAllocator::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanMemoryAllocator();
	}
	return instance_;
}
