#include <Engine/Rendering/RenderPass/BaseRenderPass.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Device/VulkanDevice.h>


ScrapEngine::Render::BaseRenderPass::~BaseRenderPass()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyRenderPass(render_pass_);
}

vk::RenderPass* ScrapEngine::Render::BaseRenderPass::get_render_pass()
{
	return &render_pass_;
}
