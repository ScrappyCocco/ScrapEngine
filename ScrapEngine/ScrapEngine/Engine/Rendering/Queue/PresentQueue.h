#pragma once

#include <vulkan/vulkan.h>
#include "GraphicsQueue.h"

namespace ScrapEngine {

	class PresentQueue
	{
	private:
		VkQueue presentationQueue;
	public:
		PresentQueue(VkDevice device, GraphicsQueue::QueueFamilyIndices indices);
		~PresentQueue();

		VkQueue getPresentQueue() const;
	};

}

