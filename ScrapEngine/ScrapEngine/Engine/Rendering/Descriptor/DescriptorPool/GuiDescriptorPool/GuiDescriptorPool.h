#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GuiDescriptorPool : public BaseDescriptorPool
		{
		public:
			GuiDescriptorPool(const std::vector<vk::Image>* swap_chain_images);
		};
	}
}
