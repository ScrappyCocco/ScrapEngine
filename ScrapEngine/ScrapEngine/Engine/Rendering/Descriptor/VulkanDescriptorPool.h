#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanDescriptorPool
		{
		private:
			vk::DescriptorPool descriptor_pool_;
		public:
			VulkanDescriptorPool(const std::vector<vk::Image>* swap_chain_images);
			~VulkanDescriptorPool();

			vk::DescriptorPool* get_descriptor_pool();
		};
	}
}
