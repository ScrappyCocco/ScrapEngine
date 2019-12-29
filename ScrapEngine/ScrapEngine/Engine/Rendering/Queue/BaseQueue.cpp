#include <Engine/Rendering/Queue/BaseQueue.h>

ScrapEngine::Render::BaseQueue::~BaseQueue()
{
	//Empty here
}

vk::Queue* ScrapEngine::Render::BaseQueue::get_queue()
{
	return &queue_;
}

ScrapEngine::Render::BaseQueue::operator vk::Queue() const
{
	return queue_;
}
