#include <Engine/Rendering/Texture/ColorResources/VulkanColorResources.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::VulkanColorResources::VulkanColorResources(const vk::SampleCountFlagBits msaa_samples,
                                                                VulkanSwapChain* swap_chain_ref)
{
	const vk::Format color_format = swap_chain_ref->get_swap_chain_image_format();

	BaseTexture::create_image(swap_chain_ref->get_swap_chain_extent().width,
	                          swap_chain_ref->get_swap_chain_extent().height, color_format,
	                          vk::ImageTiling::eOptimal,
	                          vk::ImageUsageFlagBits::eTransientAttachment |
	                          vk::ImageUsageFlagBits::eColorAttachment,
	                          vk::MemoryPropertyFlagBits::eDeviceLocal,
	                          color_image_, color_image_memory_, 1, msaa_samples);
	color_image_view_ = TextureImageView::create_image_view(
		&color_image_, color_format, vk::ImageAspectFlagBits::eColor, 1);

	BaseTexture::transition_image_layout(&color_image_, color_format, vk::ImageLayout::eUndefined,
	                                     vk::ImageLayout::eColorAttachmentOptimal, 1);
}


ScrapEngine::Render::VulkanColorResources::~VulkanColorResources()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyImageView(color_image_view_);
	VulkanDevice::get_instance()->get_logical_device()->destroyImage(color_image_);
	VulkanDevice::get_instance()->get_logical_device()->freeMemory(color_image_memory_);
}

vk::Image* ScrapEngine::Render::VulkanColorResources::get_color_image()
{
	return &color_image_;
}

vk::ImageView* ScrapEngine::Render::VulkanColorResources::get_color_image_view()
{
	return &color_image_view_;
}
