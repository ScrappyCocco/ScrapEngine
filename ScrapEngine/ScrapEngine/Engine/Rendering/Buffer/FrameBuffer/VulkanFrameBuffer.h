#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <Engine/Rendering/SwapChain/VulkanImageView.h>


namespace ScrapEngine
{
	namespace Render
	{
		class VulkanFrameBuffer
		{
		private:
			std::vector<vk::Framebuffer> swap_chain_framebuffers_;
		public:
			VulkanFrameBuffer(VulkanImageView* input_image_view_ref,
			                  const vk::Extent2D* input_swap_chain_extent,
			                  vk::ImageView* depth_image_view, vk::ImageView* color_image_view);
			~VulkanFrameBuffer();

			const std::vector<vk::Framebuffer>* get_swap_chain_framebuffers_vector() const;
			size_t get_swap_chain_framebuffers_vector_size() const;
		};
	}
}
