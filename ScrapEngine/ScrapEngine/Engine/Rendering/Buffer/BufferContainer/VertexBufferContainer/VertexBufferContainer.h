#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Buffer/BufferContainer/BufferContainer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VertexBufferContainer : public BufferContainer
		{
		private:
			const std::vector<ScrapEngine::Vertex>* vertices_;
		public:
			VertexBufferContainer(vk::Buffer* input_buffer, const std::vector<ScrapEngine::Vertex>* input_vertices);
			~VertexBufferContainer() = default;

			const std::vector<ScrapEngine::Vertex>* get_vector() const;
		};
	}
}
