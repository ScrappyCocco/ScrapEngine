#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <array>
#include <Engine/Rendering/Base/StaticTypes.h>

ScrapEngine::Render::VulkanFrameBuffer::VulkanFrameBuffer(ScrapEngine::Render::VulkanImageView* input_image_view_ref,
                                                          const vk::Extent2D* input_swap_chain_extent,
                                                          vk::ImageView* depth_image_view,
                                                          vk::ImageView* color_image_view)
{
	const std::vector<vk::ImageView>* swap_chain_image_views = input_image_view_ref->get_swap_chain_image_views_vector();

	swap_chain_framebuffers_.resize(swap_chain_image_views->size());

	for (size_t i = 0; i < swap_chain_image_views->size(); i++)
	{
		std::array<vk::ImageView, 3> attachments = {
			*color_image_view,
			*depth_image_view,
			(*swap_chain_image_views)[i]
		};

		vk::FramebufferCreateInfo framebuffer_info(
			vk::FramebufferCreateFlags(),
			*VulkanRenderPass::static_render_pass_ref,
			static_cast<uint32_t>(attachments.size()),
			attachments.data(),
			input_swap_chain_extent->width,
			input_swap_chain_extent->height,
			1
		);

		if (VulkanDevice::static_logic_device_ref->createFramebuffer(&framebuffer_info, nullptr,
		                                                          &swap_chain_framebuffers_[i]) != vk::Result::eSuccess)
		{
			throw std::runtime_error("VulkanFrameBuffer: Failed to create framebuffer!");
		}
	}
}

ScrapEngine::Render::VulkanFrameBuffer::~VulkanFrameBuffer()
{
	for (auto const framebuffer : swap_chain_framebuffers_)
	{
		VulkanDevice::static_logic_device_ref->destroyFramebuffer(framebuffer);
	}
}

const std::vector<vk::Framebuffer>* ScrapEngine::Render::VulkanFrameBuffer::get_swap_chain_framebuffers_vector() const
{
	return &swap_chain_framebuffers_;
}

size_t ScrapEngine::Render::VulkanFrameBuffer::get_swap_chain_framebuffers_vector_size() const
{
	return swap_chain_framebuffers_.size();
}
