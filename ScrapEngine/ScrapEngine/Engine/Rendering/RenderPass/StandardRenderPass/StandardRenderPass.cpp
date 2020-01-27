#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>
#include <stdexcept>
#include <array>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>

//Init static instance reference

ScrapEngine::Render::StandardRenderPass* ScrapEngine::Render::StandardRenderPass::instance_ = nullptr;

//Class

void ScrapEngine::Render::StandardRenderPass::init(const vk::Format& swap_chain_image_format,
                                                   const vk::SampleCountFlagBits msaa_samples)
{
	msaa_samples_ = msaa_samples;
	
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
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eClear,
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

	std::array<vk::AttachmentDescription, 3> attachments = {
		color_attachment, depth_attachment, color_attachment_resolve
	};

	std::array< vk::SubpassDependency, 2> dependencies;

	dependencies[0].setSrcSubpass(VK_SUBPASS_EXTERNAL);
	dependencies[0].setDstSubpass(0);
	dependencies[0].setSrcStageMask(vk::PipelineStageFlagBits::eBottomOfPipe);
	dependencies[0].setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
	dependencies[0].setSrcAccessMask(vk::AccessFlagBits::eMemoryRead);
	dependencies[0].setDstAccessMask(vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite);
	dependencies[0].setDependencyFlags(vk::DependencyFlagBits::eByRegion);

	dependencies[1].setSrcSubpass(0);
	dependencies[1].setDstSubpass(VK_SUBPASS_EXTERNAL);
	dependencies[1].setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
	dependencies[1].setDstStageMask(vk::PipelineStageFlagBits::eBottomOfPipe);
	dependencies[1].setSrcAccessMask(vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite);
	dependencies[0].setDstAccessMask(vk::AccessFlagBits::eMemoryRead);
	dependencies[1].setDependencyFlags(vk::DependencyFlagBits::eByRegion);

	vk::RenderPassCreateInfo render_pass_info(
		vk::RenderPassCreateFlags(),
		static_cast<uint32_t>(attachments.size()),
		attachments.data(),
		1,
		&subpass,
		static_cast<uint32_t>(dependencies.size()),
		dependencies.data()
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createRenderPass(&render_pass_info, nullptr, &render_pass_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("VulkanRenderPass: Failed to create render pass!");
	}
}

ScrapEngine::Render::StandardRenderPass* ScrapEngine::Render::StandardRenderPass::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new StandardRenderPass();
	}
	return instance_;
}

vk::SampleCountFlagBits ScrapEngine::Render::StandardRenderPass::get_msaa_samples() const
{
	return msaa_samples_;
}
