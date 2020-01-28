#include <Engine/Rendering/RenderPass/ShadowmappingRenderPass/ShadowmappingRenderPass.h>
#include <array>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::ShadowmappingRenderPass::ShadowmappingRenderPass(const vk::Format& depth_format)
{
	const vk::AttachmentDescription attachment_description(
		vk::AttachmentDescriptionFlags(),
		depth_format,
		vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eDepthStencilReadOnlyOptimal
	);

	vk::AttachmentReference depth_attachment_ref(
		0,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	vk::SubpassDescription subpass(
		vk::SubpassDescriptionFlags(),
		vk::PipelineBindPoint::eGraphics
	);
	subpass.setColorAttachmentCount(0);
	subpass.setPDepthStencilAttachment(&depth_attachment_ref);

	// Use subpass dependencies for layout transitions
	std::array<vk::SubpassDependency, 2> dependencies;

	dependencies[0] = vk::SubpassDependency(
		VK_SUBPASS_EXTERNAL,
		0,
		vk::PipelineStageFlagBits::eFragmentShader,
		vk::PipelineStageFlagBits::eEarlyFragmentTests,
		vk::AccessFlagBits::eShaderRead,
		vk::AccessFlagBits::eDepthStencilAttachmentWrite,
		vk::DependencyFlagBits::eByRegion
	);

	dependencies[1] = vk::SubpassDependency(
		0,
		VK_SUBPASS_EXTERNAL,
		vk::PipelineStageFlagBits::eLateFragmentTests,
		vk::PipelineStageFlagBits::eFragmentShader,
		vk::AccessFlagBits::eDepthStencilAttachmentWrite,
		vk::AccessFlagBits::eShaderRead,
		vk::DependencyFlagBits::eByRegion
	);

	vk::RenderPassCreateInfo render_pass_info(
		vk::RenderPassCreateFlags(),
		1,
		&attachment_description,
		1,
		&subpass,
		static_cast<uint32_t>(dependencies.size()),
		dependencies.data()
	);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createRenderPass(&render_pass_info, nullptr, &render_pass_);
	
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "ShadowmappingRenderPass: Failed to create render pass!");
	}
}

