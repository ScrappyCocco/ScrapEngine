#include "GraphicsQueue.h"
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::Queue* ScrapEngine::Render::GraphicsQueue::StaticGraphicsQueueRef = nullptr;

//Class

ScrapEngine::Render::GraphicsQueue::GraphicsQueue(QueueFamilyIndices indices)
{
	VulkanDevice::static_logic_device_ref->getQueue(indices.graphicsFamily, 0, &graphicsQueue);
	StaticGraphicsQueueRef = &graphicsQueue;
}

ScrapEngine::Render::GraphicsQueue::~GraphicsQueue()
{

}

vk::Queue* ScrapEngine::Render::GraphicsQueue::getgraphicsQueue()
{
	return &graphicsQueue;
}
