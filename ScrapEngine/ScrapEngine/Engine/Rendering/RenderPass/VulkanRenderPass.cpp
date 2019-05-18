#include "VulkanRenderPass.h"

#include <stdexcept>
#include <array>
#include "../DepthResources/VulkanDepthResources.h"
#include "../Base/StaticTypes.h"

//Init Static Members

const vk::RenderPass* ScrapEngine::Render::VulkanRenderPass::StaticRenderPassRef = nullptr;

//Class

ScrapEngine::Render::VulkanRenderPass::VulkanRenderPass(const vk::Format& swapChainImageFormat, vk::SampleCountFlagBits msaaSamples)
{
	vk::AttachmentDescription colorAttachment(
		vk::AttachmentDescriptionFlags(),
		swapChainImageFormat,
		msaaSamples,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::AttachmentDescription depthAttachment(
		vk::AttachmentDescriptionFlags(),
		VulkanDepthResources::find_depth_format(),
		msaaSamples,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eDontCare,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	vk::AttachmentDescription colorAttachmentResolve(
		vk::AttachmentDescriptionFlags(),
		swapChainImageFormat,
		vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::ePresentSrcKHR
	);

	vk::AttachmentReference colorAttachmentRef(
		0,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::AttachmentReference depthAttachmentRef(
		1,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	vk::AttachmentReference colorAttachmentResolveRef(
		2,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::SubpassDescription subpass(
		vk::SubpassDescriptionFlags(),
		vk::PipelineBindPoint::eGraphics,
		0, nullptr,
		1, &colorAttachmentRef,
		&colorAttachmentResolveRef, 
		&depthAttachmentRef
	);

	vk::SubpassDependency dependency(
		VK_SUBPASS_EXTERNAL, 
		0,
		vk::PipelineStageFlagBits::eColorAttachmentOutput,
		vk::PipelineStageFlagBits::eColorAttachmentOutput,
		vk::AccessFlags(),
		vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite
	);

	std::array<vk::AttachmentDescription, 3> attachments = { colorAttachment, depthAttachment, colorAttachmentResolve };

	vk::RenderPassCreateInfo renderPassInfo(
		vk::RenderPassCreateFlags(),
		static_cast<uint32_t>(attachments.size()),
		attachments.data(),
		1,
		&subpass,
		1,
		&dependency
	);

	if (VulkanDevice::static_logic_device_ref->createRenderPass(&renderPassInfo, nullptr, &renderPass) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanRenderPass: Failed to create render pass!");
	}

	StaticRenderPassRef = &renderPass;
}

ScrapEngine::Render::VulkanRenderPass::~VulkanRenderPass()
{
	VulkanDevice::static_logic_device_ref->destroyRenderPass(renderPass);
}

vk::RenderPass* ScrapEngine::Render::VulkanRenderPass::getRenderPass()
{
	return &renderPass;
}
