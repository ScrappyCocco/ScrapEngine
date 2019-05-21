#include <Engine/Rendering/Queue/BaseQueue.h>
#include <Engine/Rendering/Base/StaticTypes.h>

ScrapEngine::Render::BaseQueue::~BaseQueue()
{
	//Empty here
}

vk::Queue* ScrapEngine::Render::BaseQueue::get_queue()
{
	return &queue_;
}
