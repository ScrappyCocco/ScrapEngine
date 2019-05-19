#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {
	namespace Render {
		class GraphicsQueue
		{
		private:
			vk::Queue graphics_queue_;
		public:
			struct QueueFamilyIndices {
				int graphics_family = -1;
				int present_family = -1;

				bool is_complete() const {
					return graphics_family >= 0 && present_family >= 0;
				}
			};

			static const vk::Queue* static_graphics_queue_ref;

			GraphicsQueue(QueueFamilyIndices indices);
			~GraphicsQueue();

			vk::Queue* get_graphics_queue();
		};
	}
}

