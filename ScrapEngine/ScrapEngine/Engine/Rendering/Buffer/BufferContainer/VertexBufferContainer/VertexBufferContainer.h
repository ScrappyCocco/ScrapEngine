#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Buffer/BufferContainer/BufferContainer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VertexBufferContainer : public BufferContainer
		{
		private:
			const std::vector<Vertex>* vertices_;
		public:
			VertexBufferContainer(vk::Buffer* input_buffer, const std::vector<Vertex>* input_vertices);
			~VertexBufferContainer() = default;

			const std::vector<Vertex>* get_vector() const;
		};
	}
}
