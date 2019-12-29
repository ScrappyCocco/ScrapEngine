#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>
#include <Engine/Rendering/Base/Vertex.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VertexBuffer
		{
		private:
			vk::Buffer vertex_buffer_;
			vk::DeviceMemory vertex_buffer_memory_;
		public:
			VertexBuffer(const std::vector<Vertex>* vertices);
			~VertexBuffer();

			vk::Buffer* get_vertex_buffer();
		};
	}
}
