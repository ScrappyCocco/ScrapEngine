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

			//Singleton static instance
			static VulkanCommandPool* instance_;

			//The constructor is private because this class is a Singleton
			VulkanCommandPool() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(BaseQueue::QueueFamilyIndices queue_family_indices);

			~VulkanCommandPool();

			//Singleton static function to get or create a class instance
			static VulkanCommandPool* get_instance();

			vk::CommandPool* get_command_pool();
		};
	}
}
