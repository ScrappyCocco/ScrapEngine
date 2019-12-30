#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanMemoryAllocator
		{
		private:
			//Singleton static instance
			static VulkanMemoryAllocator* instance_;

			VmaAllocator allocator_;

			//The constructor is private because this class is a Singleton
			VulkanMemoryAllocator() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(vk::PhysicalDevice physical_device, vk::Device logical_device);

			~VulkanMemoryAllocator();

			static VulkanMemoryAllocator* get_instance();

			void destroy_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc) const;

			void map_buffer_allocation(VmaAllocation& buff_alloc, void** data) const;
			void unmap_buffer_allocation(VmaAllocation& buff_alloc) const;
			void flush_buffer_allocation(VmaAllocation& buff_alloc, vk::DeviceSize size, vk::DeviceSize offset) const;
			void bind_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc, vk::DeviceSize offset = 0) const;

			void create_generic_buffer(vk::BufferCreateInfo* buff_info, VmaAllocationCreateInfo* alloc_info,
			                           vk::Buffer& buffer, VmaAllocation& buff_alloc) const;
		private:
			static VkBufferCreateInfo* convert_buffer_create_info(vk::BufferCreateInfo* buffer_info);
		};
	}
}
