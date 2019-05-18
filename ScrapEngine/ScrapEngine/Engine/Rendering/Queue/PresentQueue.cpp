#include "PresentQueue.h"
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::Queue* ScrapEngine::Render::PresentQueue::StaticPresentationQueueRef = nullptr;

//Class

ScrapEngine::Render::PresentQueue::PresentQueue(GraphicsQueue::QueueFamilyIndices indices)
{
	VulkanDevice::static_logic_device_ref->getQueue(indices.presentFamily, 0, &presentationQueue);
	StaticPresentationQueueRef = &presentationQueue;
}

ScrapEngine::Render::PresentQueue::~PresentQueue()
{

}

vk::Queue* ScrapEngine::Render::PresentQueue::getPresentQueue()
{
	return &presentationQueue;
}
