#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class GenericBuffer
		{
		private:
			vk::Buffer buffer_ = nullptr;
			vk::DeviceMemory buffer_memory_ = nullptr;
			vk::DescriptorBufferInfo descriptor_;

			void* mapped_memory_ = nullptr;
		public:
			GenericBuffer() = default;
			~GenericBuffer();

			void create_buffer(const vk::BufferCreateInfo& crate_info);

			void setup_descriptor(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);
			void map(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);
			void unmap();
			void flush(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0) const;
			void bind(vk::DeviceSize offset = 0) const;
			void destroy() const;

			vk::Buffer* get_buffer();
			void* get_mapped_memory() const;
		};
	}
}
