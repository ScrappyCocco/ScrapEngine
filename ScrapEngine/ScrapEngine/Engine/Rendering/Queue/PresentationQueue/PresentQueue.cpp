#include <Engine/Rendering/Queue/PresentationQueue/PresentQueue.h>
#include "Engine/Rendering/Device/VulkanDevice.h"

//Init static instance reference

ScrapEngine::Render::PresentQueue* ScrapEngine::Render::PresentQueue::instance_ = nullptr;

//Class

void ScrapEngine::Render::PresentQueue::init(const QueueFamilyIndices indices)
{
	VulkanDevice::get_instance()->get_logical_device()->getQueue(indices.present_family, 0, &queue_);
}

ScrapEngine::Render::PresentQueue* ScrapEngine::Render::PresentQueue::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new PresentQueue();
	}
	return instance_;
}
