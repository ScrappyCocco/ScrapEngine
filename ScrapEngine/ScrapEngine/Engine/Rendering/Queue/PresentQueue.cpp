#include <Engine/Rendering/Queue/PresentQueue.h>
#include <Engine/Rendering/Base/StaticTypes.h>

//Init Static Members

const vk::Queue* ScrapEngine::Render::PresentQueue::static_presentation_queue_ref = nullptr;

//Class

ScrapEngine::Render::PresentQueue::PresentQueue(GraphicsQueue::QueueFamilyIndices indices)
{
	VulkanDevice::static_logic_device_ref->getQueue(indices.present_family, 0, &presentation_queue_);
	static_presentation_queue_ref = &presentation_queue_;
}

vk::Queue* ScrapEngine::Render::PresentQueue::get_present_queue()
{
	return &presentation_queue_;
}
