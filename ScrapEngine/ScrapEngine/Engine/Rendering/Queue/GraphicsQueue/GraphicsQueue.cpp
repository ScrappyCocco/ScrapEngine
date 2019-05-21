#include <Engine/Rendering/Queue/GraphicsQueue/GraphicsQueue.h>
#include <Engine/Rendering/Base/StaticTypes.h>

//Init Static Members

const vk::Queue* ScrapEngine::Render::GraphicsQueue::static_graphics_queue_ref = nullptr;

//Class

ScrapEngine::Render::GraphicsQueue::GraphicsQueue(const QueueFamilyIndices indices)
{
	VulkanDevice::static_logic_device_ref->getQueue(indices.graphics_family, 0, &queue_);
	static_graphics_queue_ref = &queue_;
}
