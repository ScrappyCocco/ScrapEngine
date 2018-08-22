#pragma once

#include <vulkan/vulkan.h>

namespace ScrapEngine {

	class GraphicsQueue
	{
	private:
		VkQueue graphicsQueue;
	public:
		struct QueueFamilyIndices {
			int graphicsFamily = -1;
			int presentFamily = -1;

			bool isComplete() {
				return graphicsFamily >= 0 && presentFamily >= 0;
			}
		};

		GraphicsQueue(VkDevice device, QueueFamilyIndices indices);
		~GraphicsQueue();

		VkQueue getgraphicsQueue() const;
	};

}

