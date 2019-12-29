#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>
#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardDescriptorPool : public BaseDescriptorPool
		{
		public:
			StandardDescriptorPool(const std::vector<vk::Image>* swap_chain_images);
			~StandardDescriptorPool() = default;
		};
	}
}
