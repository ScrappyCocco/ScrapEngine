#define VMA_IMPLEMENTATION

#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

//Init static instance reference

ScrapEngine::Render::VulkanMemoryAllocator* ScrapEngine::Render::VulkanMemoryAllocator::instance_ = nullptr;

//Class

void ScrapEngine::Render::VulkanMemoryAllocator::init(const vk::PhysicalDevice physical_device,
                                                      const vk::Device logical_device)
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

void ScrapEngine::Render::VulkanMemoryAllocator::destroy_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc) const
{
	vmaDestroyBuffer(allocator_, buffer, buff_alloc);
}

void ScrapEngine::Render::VulkanMemoryAllocator::map_buffer_allocation(VmaAllocation& buff_alloc, void** data) const
{
	const VkResult res = vmaMapMemory(allocator_, buff_alloc, &(*data));

	if (res != VK_SUCCESS)
	{
		throw std::runtime_error("[VulkanMemoryAllocator][map_buffer_allocation] Unable to map buffer memory!");
	}
}

void ScrapEngine::Render::VulkanMemoryAllocator::unmap_buffer_allocation(VmaAllocation& buff_alloc) const
{
	vmaUnmapMemory(allocator_, buff_alloc);
}

void ScrapEngine::Render::VulkanMemoryAllocator::flush_buffer_allocation(VmaAllocation& buff_alloc,
                                                                         const vk::DeviceSize size,
                                                                         const vk::DeviceSize offset) const
{
	vmaFlushAllocation(allocator_, buff_alloc, offset, size);
}

void ScrapEngine::Render::VulkanMemoryAllocator::bind_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc,
                                                             const vk::DeviceSize offset) const
{
	const VkResult res = vmaBindBufferMemory2(allocator_, buff_alloc, offset, buffer, nullptr);

	if (res != VK_SUCCESS)
	{
		throw std::runtime_error("[VulkanMemoryAllocator][bind_buffer] Unable to bind buffer memory!");
	}
}

void ScrapEngine::Render::VulkanMemoryAllocator::create_generic_buffer(vk::BufferCreateInfo* buff_info,
                                                                       VmaAllocationCreateInfo* alloc_info,
                                                                       vk::Buffer& buffer,
                                                                       VmaAllocation& buff_alloc) const
{
	VkBuffer alloc_buffer;
	VkBufferCreateInfo* conv_buff_info = convert_buffer_create_info(buff_info);

	const VkResult res = vmaCreateBuffer(allocator_, conv_buff_info, alloc_info, &alloc_buffer, &buff_alloc, nullptr);

	if (res != VK_SUCCESS)
	{
		throw std::runtime_error("[VulkanMemoryAllocator][create_generic_buffer] Unable to create buffer!");
	}

	//Copy the allocated buffer to the c++ bindings
	buffer = alloc_buffer;
}

VkBufferCreateInfo* ScrapEngine::Render::VulkanMemoryAllocator::convert_buffer_create_info(
	vk::BufferCreateInfo* buffer_info)
{
	return reinterpret_cast<VkBufferCreateInfo*>(buffer_info);
}
