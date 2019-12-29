#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseDescriptorPool
		{
		protected:
			vk::DescriptorPool descriptor_pool_;
		public:
			BaseDescriptorPool() = default;
			virtual ~BaseDescriptorPool() = 0;

			vk::DescriptorPool* get_descriptor_pool();
		};
	}
}
