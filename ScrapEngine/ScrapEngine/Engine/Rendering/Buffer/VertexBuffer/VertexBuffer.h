#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Base/Vertex.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class VertexBuffer
		{
		private:
			vk::Buffer vertex_buffer_;
			VmaAllocation vertex_buffer_memory_;
		public:
			VertexBuffer(const std::vector<Vertex>* vertices);
			~VertexBuffer();

			vk::Buffer* get_vertex_buffer();
		};
	}
}
