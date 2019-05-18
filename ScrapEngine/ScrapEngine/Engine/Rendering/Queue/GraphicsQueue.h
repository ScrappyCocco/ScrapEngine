#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {
	namespace Render {
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

			static const vk::Queue* StaticGraphicsQueueRef;

			GraphicsQueue(QueueFamilyIndices indices);
			~GraphicsQueue();

			vk::Queue* getgraphicsQueue();
		};
	}
}

