#include <Engine/Rendering/Buffer/FrameBuffer/ShadowmappingFrameBuffer/ShadowmappingFrameBufferAttachment.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::ShadowmappingFrameBufferAttachment::ShadowmappingFrameBufferAttachment(const int32_t width,
                                                                                            const int32_t height,
                                                                                            const vk::Format
                                                                                            depth_format)
{
	// Create the image
	
	const vk::ImageCreateInfo image_info(
		vk::ImageCreateFlags(),
		vk::ImageType::e2D,
		depth_format,
		vk::Extent3D(width, height, 1),
		1,
		1,
		vk::SampleCountFlagBits::e1,
		vk::ImageTiling::eOptimal,
		vk::ImageUsageFlagBits::eDepthStencilAttachment | vk::ImageUsageFlagBits::eSampled,
		vk::SharingMode::eExclusive
	);

	VulkanMemoryAllocator::get_instance()->create_texture_image(&image_info, image_, image_memory_);

	// Create the image view

	vk::ImageViewCreateInfo depth_stencil_view(
		vk::ImageViewCreateFlags(),
		image_,
		vk::ImageViewType::e2D,
		depth_format
		);

	const vk::ImageSubresourceRange depth_stencil_view_sbr(
		vk::ImageAspectFlagBits::eDepth,
		0,
		1,
		0,
		1
	);

	depth_stencil_view.setSubresourceRange(depth_stencil_view_sbr);

	VulkanDevice::get_instance()->get_logical_device()->createImageView(&depth_stencil_view, nullptr, &image_view_);
}

ScrapEngine::Render::ShadowmappingFrameBufferAttachment::~ShadowmappingFrameBufferAttachment()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyImageView(image_view_);
	VulkanMemoryAllocator::get_instance()->destroy_image(image_, image_memory_);
}

vk::Image* ScrapEngine::Render::ShadowmappingFrameBufferAttachment::get_image()
{
	return &image_;
}

vk::ImageView* ScrapEngine::Render::ShadowmappingFrameBufferAttachment::get_image_view()
{
	return &image_view_;
}
