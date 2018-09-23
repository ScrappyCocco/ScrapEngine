#include "GraphicsQueue.h"

ScrapEngine::GraphicsQueue::GraphicsQueue(vk::Device* device, QueueFamilyIndices indices)
{
	device->getQueue(indices.graphicsFamily, 0, &graphicsQueue);
}

ScrapEngine::GraphicsQueue::~GraphicsQueue()
{

}

vk::Queue* ScrapEngine::GraphicsQueue::getgraphicsQueue()
{
	return &graphicsQueue;
}
