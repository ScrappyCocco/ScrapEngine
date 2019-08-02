#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>

ScrapEngine::Render::IndicesBufferContainer::IndicesBufferContainer(vk::Buffer* input_buffer,
                                                                    const std::vector<uint32_t>* input_indices)
	: BufferContainer(input_buffer), indices_(input_indices)
{
}

const std::vector<uint32_t>* ScrapEngine::Render::IndicesBufferContainer::get_vector() const
{
	return indices_;
}
