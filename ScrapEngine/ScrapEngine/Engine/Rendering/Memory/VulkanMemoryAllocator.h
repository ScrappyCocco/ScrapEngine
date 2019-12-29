#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanMemoryAllocator
		{
		private:
			//Singleton static instance
			static VulkanMemoryAllocator* instance_;

			VmaAllocator allocator_;

			//The constructor is private because this class is a Singleton
			VulkanMemoryAllocator() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(vk::PhysicalDevice physical_device, vk::Device logical_device);
			
			~VulkanMemoryAllocator();

			static VulkanMemoryAllocator* get_instance();
		};
	}
}

