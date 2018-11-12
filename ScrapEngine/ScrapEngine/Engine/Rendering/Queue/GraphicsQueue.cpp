#include "GraphicsQueue.h"
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::Queue* ScrapEngine::GraphicsQueue::StaticGraphicsQueueRef = nullptr;

//Class

ScrapEngine::GraphicsQueue::GraphicsQueue(QueueFamilyIndices indices)
{
	VulkanDevice::StaticLogicDeviceRef->getQueue(indices.graphicsFamily, 0, &graphicsQueue);
	StaticGraphicsQueueRef = &graphicsQueue;
}

ScrapEngine::GraphicsQueue::~GraphicsQueue()
{

}

vk::Queue* ScrapEngine::GraphicsQueue::getgraphicsQueue()
{
	return &graphicsQueue;
}
