#include <Engine/Rendering/Buffer/BufferContainer/BufferContainer.h>

ScrapEngine::Render::BufferContainer::BufferContainer(vk::Buffer* input_buffer) : buffer_(input_buffer)
{
	
}

ScrapEngine::Render::BufferContainer::~BufferContainer()
{
	//Empty here
}

vk::Buffer* ScrapEngine::Render::BufferContainer::get_buffer() const
{
	return buffer_;
}
