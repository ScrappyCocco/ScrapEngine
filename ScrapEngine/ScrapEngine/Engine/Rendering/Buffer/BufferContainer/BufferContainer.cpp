#include <Engine/Rendering/Buffer/BufferContainer/BufferContainer.h>

ScrapEngine::Render::BufferContainer::BufferContainer(vk::Buffer* input_buffer) : buffer_(input_buffer)
{
	
}

vk::Buffer* ScrapEngine::Render::BufferContainer::getbuffer() const
{
	return buffer_;
}
