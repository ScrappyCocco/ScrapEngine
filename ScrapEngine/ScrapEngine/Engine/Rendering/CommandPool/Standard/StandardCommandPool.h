#pragma once

#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardCommandPool : public VulkanCommandPool
		{
		public:
			StandardCommandPool() = default;
			~StandardCommandPool() = default;
		};
	}
}
