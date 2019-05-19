#pragma once

#include <vulkan/vulkan.hpp>
#include "GraphicsQueue.h"

namespace ScrapEngine
{
	namespace Render
	{
		class PresentQueue
		{
		private:
			vk::Queue presentation_queue_;
		public:
			static const vk::Queue* static_presentation_queue_ref;

			PresentQueue(GraphicsQueue::QueueFamilyIndices indices);
			~PresentQueue();

			vk::Queue* get_present_queue();
		};
	}
}
