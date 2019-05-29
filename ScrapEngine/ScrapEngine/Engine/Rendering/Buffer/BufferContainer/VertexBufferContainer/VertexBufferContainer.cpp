#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>

ScrapEngine::Render::VertexBufferContainer::VertexBufferContainer(vk::Buffer* input_buffer,
                                                                  const std::vector<Vertex>* input_vertices)
	: BufferContainer(input_buffer), vertices_(input_vertices)
{
}

const std::vector<ScrapEngine::Vertex>* ScrapEngine::Render::VertexBufferContainer::get_vector() const
{
	return vertices_;
}
