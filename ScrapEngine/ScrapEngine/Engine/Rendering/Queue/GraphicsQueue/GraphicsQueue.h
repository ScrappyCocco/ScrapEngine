#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GraphicsQueue : public BaseQueue
		{
		public:
			static const vk::Queue* static_graphics_queue_ref;

			GraphicsQueue(QueueFamilyIndices indices);
			~GraphicsQueue() = default;
		};
	}
}
