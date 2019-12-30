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
			VmaAllocation staging_buffer_memory_;
		public:
			BaseStagingBuffer() = default;

			virtual ~BaseStagingBuffer() = 0;

			vk::Buffer* get_staging_buffer();
		};
	}
}
