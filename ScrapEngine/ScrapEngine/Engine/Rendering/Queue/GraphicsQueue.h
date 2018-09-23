#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {

	class GraphicsQueue
	{
	private:
		vk::Queue graphicsQueue;
	public:
		struct QueueFamilyIndices {
			int graphicsFamily = -1;
			int presentFamily = -1;

			bool isComplete() {
				return graphicsFamily >= 0 && presentFamily >= 0;
			}
		};

		GraphicsQueue(vk::Device* device, QueueFamilyIndices indices);
		~GraphicsQueue();

		vk::Queue* getgraphicsQueue();
	};

}

