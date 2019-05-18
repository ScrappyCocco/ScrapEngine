#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {
	namespace Render {
		class VulkanRenderPass
		{
		private:
			vk::RenderPass renderPass;
		public:
			static const vk::RenderPass* StaticRenderPassRef;

			VulkanRenderPass(const vk::Format& swapChainImageFormat, vk::SampleCountFlagBits msaaSamples);
			~VulkanRenderPass();

			vk::RenderPass* getRenderPass();
		};
	}
}

