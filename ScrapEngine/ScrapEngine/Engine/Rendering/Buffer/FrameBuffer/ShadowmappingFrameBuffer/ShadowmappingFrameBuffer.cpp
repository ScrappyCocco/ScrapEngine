#include <Engine/Rendering/Buffer/FrameBuffer/ShadowmappingFrameBuffer/ShadowmappingFrameBuffer.h>
#include <array>
#include <Engine/Rendering/RenderPass/ShadowmappingRenderPass/ShadowmappingRenderPass.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::ShadowmappingFrameBuffer::ShadowmappingFrameBuffer(const int32_t width,
                                                                        const int32_t height,
                                                                        const vk::Format depth_format,
                                                                        const vk::Filter shadowmap_filter,
                                                                        BaseRenderPass* render_pass)
{
	width_ = width;
	height_ = height;

	// Create depth_attachment_ images

	depth_attachment_ = new ShadowmappingFrameBufferAttachment(width, height, depth_format);

	//Create sampler

	vk::SamplerCreateInfo sampler(
		vk::SamplerCreateFlags(),
		shadowmap_filter,
		shadowmap_filter,
		vk::SamplerMipmapMode::eLinear,
		vk::SamplerAddressMode::eClampToEdge,
		vk::SamplerAddressMode::eClampToEdge,
		vk::SamplerAddressMode::eClampToEdge,
		0.0f
	);
	sampler.setMaxAnisotropy(1.0f);
	sampler.setMinLod(0.0f);
	sampler.setMaxLod(1.0f);
	sampler.setBorderColor(vk::BorderColor::eFloatOpaqueWhite);

	VulkanDevice::get_instance()->get_logical_device()->createSampler(&sampler, nullptr, &depth_sampler_);

	// Create the framebuffer

	framebuffers_.resize(1);

	vk::FramebufferCreateInfo create_info(
		vk::FramebufferCreateFlags(),
		*render_pass->get_render_pass(),
		1,
		depth_attachment_->get_image_view(),
		width_,
		height_,
		1
	);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createFramebuffer(
		&create_info, nullptr,
		&framebuffers_[0]);

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "ShadowmappingFrameBuffer: Failed to create framebuffer!");
	}
}

ScrapEngine::Render::ShadowmappingFrameBuffer::~ShadowmappingFrameBuffer()
{
	VulkanDevice::get_instance()->get_logical_device()->destroySampler(depth_sampler_);
	delete depth_attachment_;
}

vk::Sampler* ScrapEngine::Render::ShadowmappingFrameBuffer::get_depth_sampler()
{
	return &depth_sampler_;
}

ScrapEngine::Render::ShadowmappingFrameBufferAttachment* ScrapEngine::Render::ShadowmappingFrameBuffer::
get_depth_attachment() const
{
	return depth_attachment_;
}
