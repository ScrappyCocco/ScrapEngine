#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseStagingBuffer
		{
		protected:
			vk::Buffer staging_buffer_;
			vk::DeviceMemory staging_buffer_memory_;
		public:
			BaseStagingBuffer() = default;

			virtual ~BaseStagingBuffer() = 0;

			vk::Buffer* get_staging_buffer();
			vk::DeviceMemory* get_staging_buffer_memory();
		};
	}
}
