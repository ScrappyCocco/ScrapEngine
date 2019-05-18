#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../Base/Vertex.h"

namespace ScrapEngine
{
	namespace Render
	{
		class IndexBuffer
		{
		private:
			vk::Buffer index_buffer_;
			vk::DeviceMemory index_buffer_memory_;
		public:
			IndexBuffer(const std::vector<uint32_t>* indices);
			~IndexBuffer();

			vk::Buffer* get_index_buffer();
		};
	}
}
