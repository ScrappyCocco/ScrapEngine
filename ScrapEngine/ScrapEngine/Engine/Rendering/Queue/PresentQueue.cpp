#include "PresentQueue.h"

//Init Static Members

const vk::Queue* ScrapEngine::PresentQueue::StaticPresentationQueueRef = nullptr;

//Class

ScrapEngine::PresentQueue::PresentQueue(vk::Device* device, GraphicsQueue::QueueFamilyIndices indices)
{
	device->getQueue(indices.presentFamily, 0, &presentationQueue);
	StaticPresentationQueueRef = &presentationQueue;
}

ScrapEngine::PresentQueue::~PresentQueue()
{

}

vk::Queue* ScrapEngine::PresentQueue::getPresentQueue()
{
	return &presentationQueue;
}
