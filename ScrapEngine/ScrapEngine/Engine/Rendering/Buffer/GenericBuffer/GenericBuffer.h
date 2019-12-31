#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GenericBuffer
		{
		private:
			vk::Buffer buffer_ = nullptr;
			vk::DescriptorBufferInfo descriptor_;
			VmaAllocation buffer_memory_;

			void* mapped_memory_ = nullptr;
		public:
			GenericBuffer() = default;
			~GenericBuffer();

			void create_buffer(const vk::BufferCreateInfo& crate_info);

			void setup_descriptor(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);
			void map();
			void unmap();
			void flush(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);
			void bind(vk::DeviceSize offset = 0);
			void destroy();

			vk::Buffer* get_buffer();
			void* get_mapped_memory() const;
		};
	}
}
