#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class IndexBuffer
		{
		private:
			vk::Buffer index_buffer_;
			VmaAllocation index_buffer_memory_;
		public:
			IndexBuffer(const std::vector<uint32_t>* indices);
			~IndexBuffer();

			vk::Buffer* get_index_buffer();
		};
	}
}
