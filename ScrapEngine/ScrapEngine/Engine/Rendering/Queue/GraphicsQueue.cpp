#include "GraphicsQueue.h"

ScrapEngine::GraphicsQueue::GraphicsQueue(VkDevice device, QueueFamilyIndices indices)
{
	vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
}

ScrapEngine::GraphicsQueue::~GraphicsQueue()
{
}

VkQueue ScrapEngine::GraphicsQueue::getgraphicsQueue() const
{
	return graphicsQueue;
}
