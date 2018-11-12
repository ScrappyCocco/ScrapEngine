#include "PresentQueue.h"
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::Queue* ScrapEngine::PresentQueue::StaticPresentationQueueRef = nullptr;

//Class

ScrapEngine::PresentQueue::PresentQueue(GraphicsQueue::QueueFamilyIndices indices)
{
	VulkanDevice::StaticLogicDeviceRef->getQueue(indices.presentFamily, 0, &presentationQueue);
	StaticPresentationQueueRef = &presentationQueue;
}

ScrapEngine::PresentQueue::~PresentQueue()
{

}

vk::Queue* ScrapEngine::PresentQueue::getPresentQueue()
{
	return &presentationQueue;
}
