#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanRenderPass
		{
		private:
			vk::RenderPass render_pass_;

			static VulkanRenderPass* instance_;

			VulkanRenderPass() = default;
		public:
			void init(const vk::Format& swap_chain_image_format, vk::SampleCountFlagBits msaa_samples);

			~VulkanRenderPass();

			static VulkanRenderPass* get_instance();

			vk::RenderPass* get_render_pass();
		};
	}
}
