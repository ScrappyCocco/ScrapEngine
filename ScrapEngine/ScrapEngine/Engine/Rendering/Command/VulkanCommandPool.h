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

			static VulkanCommandPool* instance_;

			VulkanCommandPool() = default;
		public:
			void init(BaseQueue::QueueFamilyIndices queue_family_indices);

			~VulkanCommandPool();

			static VulkanCommandPool* get_instance();

			vk::CommandPool* get_command_pool();
		};
	}
}
