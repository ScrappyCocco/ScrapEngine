#include "VulkanColorResources.h"
#include "TextureImage.h"
#include "TextureImageView.h"

ScrapEngine::Render::VulkanColorResources::VulkanColorResources(vk::SampleCountFlagBits msaa_samples,
                                                                ScrapEngine::Render::VulkanSwapChain* swap_chain_ref)
{
	const vk::Format color_format = swap_chain_ref->get_swap_chain_image_format();

	ScrapEngine::Render::TextureImage::create_image(swap_chain_ref->get_swap_chain_extent().width,
	                                               swap_chain_ref->get_swap_chain_extent().height, color_format,
	                                               vk::ImageTiling::eOptimal,
	                                               vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits
	                                               ::eColorAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal,
	                                               color_image_, color_image_memory_, 1, msaa_samples);
	color_image_view_ = ScrapEngine::Render::TextureImageView::create_image_view(
		&color_image_, color_format, vk::ImageAspectFlagBits::eColor, 1);

	ScrapEngine::Render::TextureImage::transition_image_layout(&color_image_, color_format, vk::ImageLayout::eUndefined,
	                                                         vk::ImageLayout::eColorAttachmentOptimal, 1);
}


ScrapEngine::Render::VulkanColorResources::~VulkanColorResources()
{
	VulkanDevice::static_logic_device_ref->destroyImageView(color_image_view_);
	VulkanDevice::static_logic_device_ref->destroyImage(color_image_);
	VulkanDevice::static_logic_device_ref->freeMemory(color_image_memory_);
}

vk::Image* ScrapEngine::Render::VulkanColorResources::get_color_image()
{
	return &color_image_;
}

vk::ImageView* ScrapEngine::Render::VulkanColorResources::get_color_image_view()
{
	return &color_image_view_;
}
