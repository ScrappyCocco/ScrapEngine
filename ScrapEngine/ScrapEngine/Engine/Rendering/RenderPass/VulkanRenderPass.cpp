#include "VulkanRenderPass.h"

#include <stdexcept>
#include <array>
#include "../DepthResources/VulkanDepthResources.h"
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::RenderPass* ScrapEngine::Render::VulkanRenderPass::static_render_pass_ref = nullptr;

//Class

ScrapEngine::Render::VulkanRenderPass::VulkanRenderPass(const vk::Format& swap_chain_image_format,
                                                        const vk::SampleCountFlagBits msaa_samples)
{
	const vk::AttachmentDescription color_attachment(
		vk::AttachmentDescriptionFlags(),
		swap_chain_image_format,
		msaa_samples,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	const vk::AttachmentDescription depth_attachment(
		vk::AttachmentDescriptionFlags(),
		VulkanDepthResources::find_depth_format(),
		msaa_samples,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eDontCare,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	const vk::AttachmentDescription color_attachment_resolve(
		vk::AttachmentDescriptionFlags(),
		swap_chain_image_format,
		vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::ePresentSrcKHR
	);

	vk::AttachmentReference color_attachment_ref(
		0,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::AttachmentReference depth_attachment_ref(
		1,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	vk::AttachmentReference color_attachment_resolve_ref(
		2,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::SubpassDescription subpass(
		vk::SubpassDescriptionFlags(),
		vk::PipelineBindPoint::eGraphics,
		0, nullptr,
		1, &color_attachment_ref,
		&color_attachment_resolve_ref,
		&depth_attachment_ref
	);

	vk::SubpassDependency dependency(
		VK_SUBPASS_EXTERNAL,
		0,
		vk::PipelineStageFlagBits::eColorAttachmentOutput,
		vk::PipelineStageFlagBits::eColorAttachmentOutput,
		vk::AccessFlags(),
		vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite
	);

	std::array<vk::AttachmentDescription, 3> attachments = {
		color_attachment, depth_attachment, color_attachment_resolve
	};

	vk::RenderPassCreateInfo render_pass_info(
		vk::RenderPassCreateFlags(),
		static_cast<uint32_t>(attachments.size()),
		attachments.data(),
		1,
		&subpass,
		1,
		&dependency
	);

	if (VulkanDevice::static_logic_device_ref->createRenderPass(&render_pass_info, nullptr, &render_pass_) != vk::Result
		::eSuccess)
	{
		throw std::runtime_error("VulkanRenderPass: Failed to create render pass!");
	}

	static_render_pass_ref = &render_pass_;
}

ScrapEngine::Render::VulkanRenderPass::~VulkanRenderPass()
{
	VulkanDevice::static_logic_device_ref->destroyRenderPass(render_pass_);
}

vk::RenderPass* ScrapEngine::Render::VulkanRenderPass::get_render_pass()
{
	return &render_pass_;
}
