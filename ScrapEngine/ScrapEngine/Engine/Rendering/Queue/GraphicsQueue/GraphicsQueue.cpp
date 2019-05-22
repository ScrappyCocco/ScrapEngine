#include <Engine/Rendering/Queue/GraphicsQueue/GraphicsQueue.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

//Init static instance reference

ScrapEngine::Render::GraphicsQueue* ScrapEngine::Render::GraphicsQueue::instance_ = nullptr;

//Class
void ScrapEngine::Render::GraphicsQueue::init(const QueueFamilyIndices indices)
{
	VulkanDevice::get_instance()->get_logical_device()->getQueue(indices.graphics_family, 0, &queue_);
}

ScrapEngine::Render::GraphicsQueue* ScrapEngine::Render::GraphicsQueue::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GraphicsQueue();
	}
	return instance_;
}
