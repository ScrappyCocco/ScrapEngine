#pragma once

#include <vulkan/vulkan.hpp>
#include "GraphicsQueue.h"

namespace ScrapEngine {

	class PresentQueue
	{
	private:
		vk::Queue presentationQueue;
	public:
		PresentQueue(vk::Device* device, GraphicsQueue::QueueFamilyIndices indices);
		~PresentQueue();

		vk::Queue* getPresentQueue();
	};

}

