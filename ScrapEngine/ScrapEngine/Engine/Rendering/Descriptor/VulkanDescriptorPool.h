#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine {
	namespace Render {
		class VulkanDescriptorPool
		{
		private:
			vk::DescriptorPool descriptorPool;
		public:
			VulkanDescriptorPool(const std::vector<vk::Image>* swapChainImages);
			~VulkanDescriptorPool();

			vk::DescriptorPool* getDescriptorPool();
		};
	}
}

