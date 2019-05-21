#pragma once

#include <vulkan/vulkan.hpp>
#include <stb_image.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StagingBuffer
		{
		private:
			vk::Buffer staging_buffer_;
			vk::DeviceMemory staging_buffer_memory_;
		public:
			StagingBuffer(const vk::DeviceSize& image_size, stbi_uc* pixels);

			template <class T>
			StagingBuffer(const vk::DeviceSize& buffer_size, const std::vector<T>* vector_data);

			~StagingBuffer();

			static void copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image, const uint32_t& width,
			                                 const uint32_t& height);
			static void copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image, const uint32_t& width,
			                                 const uint32_t& height, vk::BufferImageCopy* region, int regioncount = 1,
			                                 vk::ImageLayout layout = vk::ImageLayout::eTransferDstOptimal);


			vk::Buffer* get_staging_buffer();
			vk::DeviceMemory* get_staging_buffer_memory();
		};

		template <class T>
		inline StagingBuffer::StagingBuffer(const vk::DeviceSize& buffer_size, const std::vector<T>* vector_data)
		{
			BaseBuffer::create_buffer(buffer_size, vk::BufferUsageFlagBits::eTransferSrc,
			                          vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::
			                          eHostCoherent, staging_buffer_, staging_buffer_memory_);
			void* data;
			VulkanDevice::static_logic_device_ref->mapMemory(staging_buffer_memory_, 0, buffer_size, vk::MemoryMapFlags(),
			                                              &data);
			memcpy(data, vector_data->data(), static_cast<size_t>(buffer_size));
			VulkanDevice::static_logic_device_ref->unmapMemory(staging_buffer_memory_);
		}
	}
}
