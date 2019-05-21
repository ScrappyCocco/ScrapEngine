#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class PresentQueue : public BaseQueue
		{
		public:
			static const vk::Queue* static_presentation_queue_ref;

			PresentQueue(QueueFamilyIndices indices);
			~PresentQueue() = default;
		};
	}
}
