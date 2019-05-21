#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanCommandPool
		{
		private:
			vk::CommandPool command_pool_;
		public:
			static const vk::CommandPool* static_command_pool_ref;

			VulkanCommandPool(BaseQueue::QueueFamilyIndices queue_family_indices);
			~VulkanCommandPool();

			vk::CommandPool* get_command_pool();
		};
	}
}
