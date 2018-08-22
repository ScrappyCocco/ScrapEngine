#include "PresentQueue.h"

ScrapEngine::PresentQueue::PresentQueue(VkDevice device, GraphicsQueue::QueueFamilyIndices indices)
{
	vkGetDeviceQueue(device, indices.presentFamily, 0, &presentationQueue);
}

ScrapEngine::PresentQueue::~PresentQueue()
{

}

VkQueue ScrapEngine::PresentQueue::getPresentQueue() const
{
	return presentationQueue;
}
