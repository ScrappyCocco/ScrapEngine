#include <Engine/Rendering/Queue/PresentationQueue/PresentQueue.h>
#include <Engine/Rendering/Base/StaticTypes.h>

//Init Static Members

const vk::Queue* ScrapEngine::Render::PresentQueue::static_presentation_queue_ref = nullptr;

//Class

ScrapEngine::Render::PresentQueue::PresentQueue(const QueueFamilyIndices indices)
{
	VulkanDevice::static_logic_device_ref->getQueue(indices.present_family, 0, &queue_);
	static_presentation_queue_ref = &queue_;
}
