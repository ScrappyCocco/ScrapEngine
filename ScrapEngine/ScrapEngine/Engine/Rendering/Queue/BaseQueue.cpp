#include <Engine/Rendering/Queue/BaseQueue.h>

ScrapEngine::Render::BaseQueue::~BaseQueue()
{
	//Empty here
}

vk::Queue* ScrapEngine::Render::BaseQueue::get_queue()
{
	return &queue_;
}
