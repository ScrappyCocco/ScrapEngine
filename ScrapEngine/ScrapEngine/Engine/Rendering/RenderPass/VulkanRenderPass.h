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
		public:
			static const vk::RenderPass* static_render_pass_ref;

			VulkanRenderPass(const vk::Format& swap_chain_image_format, vk::SampleCountFlagBits msaa_samples);
			~VulkanRenderPass();

			vk::RenderPass* get_render_pass();
		};
	}
}
