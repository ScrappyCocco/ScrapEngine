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

			//-----------------------------------
			// Calls to destroy allocations
			//-----------------------------------

			void destroy_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc) const;
			void destroy_image(vk::Image& image, VmaAllocation& image_alloc) const;

			//-----------------------------------
			// Utils to bind, map and unmap memory
			//-----------------------------------

			void map_buffer_allocation(VmaAllocation& buff_alloc, void** data) const;
			void unmap_buffer_allocation(VmaAllocation& buff_alloc) const;
			void flush_buffer_allocation(VmaAllocation& buff_alloc, vk::DeviceSize size, vk::DeviceSize offset) const;
			void bind_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc, vk::DeviceSize offset = 0) const;

			//-----------------------------------
			// Calls to create buffers
			//-----------------------------------

			void create_generic_buffer(vk::BufferCreateInfo* buff_info, VmaAllocationCreateInfo* alloc_info,
			                           vk::Buffer& buffer, VmaAllocation& buff_alloc) const;

			void create_vertex_index_buffer(vk::BufferCreateInfo* buff_info, vk::Buffer& buffer,
			                                VmaAllocation& buff_alloc) const;

			void create_uniform_buffer(vk::DeviceSize size, vk::Buffer& buffer,
			                           VmaAllocation& buff_alloc) const;

			void create_transfer_staging_buffer(vk::DeviceSize size, vk::Buffer& buffer,
			                                    VmaAllocation& buff_alloc) const;

			//-----------------------------------
			// Calls to create images
			//-----------------------------------

			void create_generic_image(vk::ImageCreateInfo* image_info, VmaAllocationCreateInfo* alloc_info,
			                          vk::Image& image, VmaAllocation& image_alloc) const;

			void create_depth_image(vk::ImageCreateInfo* image_info,
			                        vk::Image& image, VmaAllocation& image_alloc) const;

			void create_texture_image(vk::ImageCreateInfo* image_info,
			                          vk::Image& image, VmaAllocation& image_alloc) const;

			void create_staging_image(vk::ImageCreateInfo* image_info,
			                          vk::Image& image, VmaAllocation& image_alloc) const;
		private:
			//-----------------------------------
			// Conversion utils because vma allocator want vk types not vk::
			//-----------------------------------

			static VkBufferCreateInfo* convert_buffer_create_info(vk::BufferCreateInfo* buffer_info);
			static VkImageCreateInfo* convert_image_create_info(vk::ImageCreateInfo* image_info);
		};
	}
}
