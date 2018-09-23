#include "PresentQueue.h"

ScrapEngine::PresentQueue::PresentQueue(vk::Device* device, GraphicsQueue::QueueFamilyIndices indices)
{
	device->getQueue(indices.presentFamily, 0, &presentationQueue);
}

ScrapEngine::PresentQueue::~PresentQueue()
{

}

vk::Queue* ScrapEngine::PresentQueue::getPresentQueue()
{
	return &presentationQueue;
}
