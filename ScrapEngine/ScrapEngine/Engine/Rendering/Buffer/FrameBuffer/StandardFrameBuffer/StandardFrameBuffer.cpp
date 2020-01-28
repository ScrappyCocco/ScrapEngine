#include <Engine/Rendering/Buffer/FrameBuffer/StandardFrameBuffer/StandardFrameBuffer.h>
#include <array>
#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::StandardFrameBuffer::StandardFrameBuffer(VulkanImageView* input_image_view_ref,
                                                              const vk::Extent2D* input_swap_chain_extent,
                                                              vk::ImageView* depth_image_view,
                                                              vk::ImageView* color_image_view)
{
	const std::vector<vk::ImageView>* swap_chain_image_views = input_image_view_ref->
		get_swap_chain_image_views_vector();

	framebuffers_.resize(swap_chain_image_views->size());

	for (size_t i = 0; i < swap_chain_image_views->size(); i++)
	{
		std::array<vk::ImageView, 3> attachments = {
			*color_image_view,
			*depth_image_view,
			(*swap_chain_image_views)[i]
		};

		vk::FramebufferCreateInfo framebuffer_info(
			vk::FramebufferCreateFlags(),
			*StandardRenderPass::get_instance(),
			static_cast<uint32_t>(attachments.size()),
			attachments.data(),
			input_swap_chain_extent->width,
			input_swap_chain_extent->height,
			1
		);

		const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createFramebuffer(
			&framebuffer_info, nullptr,
			&framebuffers_[i]);

		if (result != vk::Result::eSuccess)
		{
			Debug::DebugLog::fatal_error(result, "StandardFrameBuffer: Failed to create framebuffer!");
		}
	}
}
