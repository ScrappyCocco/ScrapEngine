#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanCommandPool
		{
		protected:
			vk::CommandPool command_pool_;

			//The constructor is private because this class is a Singleton
			VulkanCommandPool() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(BaseQueue::QueueFamilyIndices queue_family_indices,
			          const vk::CommandPoolCreateFlags& flags = vk::CommandPoolCreateFlags());

			virtual ~VulkanCommandPool() = 0;

			void reset_command_pool() const;

			//Function to get the command pool
			vk::CommandPool* get_command_pool();
			//Conversion operators
			operator vk::CommandPool() const;
		};
	}
}
