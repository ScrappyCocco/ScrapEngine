#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine {

	class VulkanDepthResources
	{
	private:
		vk::Image depthImage;
		vk::DeviceMemory depthImageMemory;
		vk::ImageView depthImageView;

		vk::Device* deviceRef;
	public:
		VulkanDepthResources(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDeviceRef, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, const vk::Extent2D* swapChainExtent, vk::SampleCountFlagBits msaaSamples);
		~VulkanDepthResources();

		static vk::Format findSupportedFormat(vk::PhysicalDevice* PhysicalDevice, const std::vector<vk::Format>& candidates, vk::ImageTiling tiling, vk::FormatFeatureFlags features);
		static vk::Format findDepthFormat(vk::PhysicalDevice* PhysicalDevice);
		static bool hasStencilComponent(vk::Format format);

		vk::Image* getDepthImage();
		vk::DeviceMemory* getDepthImageMemory();
		vk::ImageView* getDepthImageView();

	};

}

