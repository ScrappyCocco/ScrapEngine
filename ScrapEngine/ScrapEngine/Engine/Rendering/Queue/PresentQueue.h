#pragma once

#include <vulkan/vulkan.hpp>
#include "GraphicsQueue.h"

namespace ScrapEngine {
	namespace Render {
		class PresentQueue
		{
		private:
			vk::Queue presentationQueue;
		public:
			static const vk::Queue* StaticPresentationQueueRef;

			PresentQueue(GraphicsQueue::QueueFamilyIndices indices);
			~PresentQueue();

			vk::Queue* getPresentQueue();
		};
	}
}

