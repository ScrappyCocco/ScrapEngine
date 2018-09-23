#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {

	class VulkanRenderPass
	{
	private:
		vk::RenderPass renderPass;

		vk::Device* deviceRef;
	public:
		VulkanRenderPass(vk::Device* input_deviceRef, vk::Format swapChainImageFormat, vk::PhysicalDevice* PhysicalDeviceRef, vk::SampleCountFlagBits msaaSamples);
		~VulkanRenderPass();

		vk::RenderPass* getRenderPass();
	};

}

