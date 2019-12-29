#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseQueue
		{
		protected:
			vk::Queue queue_;
		public:
			struct QueueFamilyIndices
			{
				int graphics_family = -1;
				int present_family = -1;

				bool is_complete() const
				{
					return graphics_family >= 0 && present_family >= 0;
				}
			};

			BaseQueue() = default;
			virtual ~BaseQueue();

			//Function to get the queue
			vk::Queue* get_queue();
			//Conversion operators
			operator vk::Queue() const;
		};
	}
}
