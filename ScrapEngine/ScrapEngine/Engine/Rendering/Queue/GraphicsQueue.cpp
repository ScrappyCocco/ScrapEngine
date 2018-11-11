#include "GraphicsQueue.h"

//Init Static Members

const vk::Queue* ScrapEngine::GraphicsQueue::StaticGraphicsQueueRef = nullptr;

//Class

ScrapEngine::GraphicsQueue::GraphicsQueue(vk::Device* device, QueueFamilyIndices indices)
{
	device->getQueue(indices.graphicsFamily, 0, &graphicsQueue);
	StaticGraphicsQueueRef = &graphicsQueue;
}

ScrapEngine::GraphicsQueue::~GraphicsQueue()
{

}

vk::Queue* ScrapEngine::GraphicsQueue::getgraphicsQueue()
{
	return &graphicsQueue;
}
