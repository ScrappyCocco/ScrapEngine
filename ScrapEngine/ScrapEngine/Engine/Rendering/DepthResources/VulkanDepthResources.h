#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine {
	namespace Render {
		class VulkanDepthResources
		{
		private:
			vk::Image depthImage;
			vk::DeviceMemory depthImageMemory;
			vk::ImageView depthImageView;
		public:
			VulkanDepthResources(const vk::Extent2D* swapChainExtent, vk::SampleCountFlagBits msaaSamples);
			~VulkanDepthResources();

			static vk::Format findSupportedFormat(const std::vector<vk::Format>& candidates, vk::ImageTiling tiling, vk::FormatFeatureFlags features);
			static vk::Format findDepthFormat();
			static bool hasStencilComponent(const vk::Format& format);

			vk::Image* getDepthImage();
			vk::DeviceMemory* getDepthImageMemory();
			vk::ImageView* getDepthImageView();

		};
	}
}

