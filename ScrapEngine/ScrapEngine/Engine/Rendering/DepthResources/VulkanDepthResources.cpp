#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::VulkanDepthResources::VulkanDepthResources(const vk::Extent2D* swap_chain_extent,
                                                                const vk::SampleCountFlagBits msaa_samples)
{
	const vk::Format depth_format = find_depth_format();

	const vk::ImageCreateInfo image_info(
		vk::ImageCreateFlags(),
		vk::ImageType::e2D,
		depth_format,
		vk::Extent3D(swap_chain_extent->width, swap_chain_extent->height, 1),
		1,
		1,
		msaa_samples,
		vk::ImageTiling::eOptimal,
		vk::ImageUsageFlagBits::eDepthStencilAttachment,
		vk::SharingMode::eExclusive
	);

	VulkanMemoryAllocator::get_instance()->
		create_texture_image(&image_info, depth_image_, depth_image_memory_);

	depth_image_view_ = TextureImageView::create_image_view(&depth_image_, depth_format,
	                                                        vk::ImageAspectFlagBits::eDepth,
	                                                        1);

	BaseTexture::transition_image_layout(&depth_image_, depth_format, vk::ImageLayout::eUndefined,
	                                     vk::ImageLayout::eDepthStencilAttachmentOptimal, 1);
}


ScrapEngine::Render::VulkanDepthResources::~VulkanDepthResources()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyImageView(depth_image_view_);
	VulkanMemoryAllocator::get_instance()->destroy_image(depth_image_, depth_image_memory_);
}

vk::Format ScrapEngine::Render::VulkanDepthResources::find_supported_format(
	const std::vector<vk::Format>& candidates, const vk::ImageTiling tiling, const vk::FormatFeatureFlags& features)
{
	for (vk::Format format : candidates)
	{
		vk::FormatProperties props;
		VulkanDevice::get_instance()->get_physical_device()->getFormatProperties(format, &props);

		if (tiling == vk::ImageTiling::eLinear && (props.linearTilingFeatures & features) == features)
		{
			return format;
		}
		else if (tiling == vk::ImageTiling::eOptimal && (props.optimalTilingFeatures & features) == features)
		{
			return format;
		}
	}

	Debug::DebugLog::fatal_error(vk::Result(-13), "VulkanDepthResources: Failed to find supported format!");
	return vk::Format();
}

vk::Format ScrapEngine::Render::VulkanDepthResources::find_depth_format()
{
	return find_supported_format(
		{
			vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint
		},
		vk::ImageTiling::eOptimal,
		vk::FormatFeatureFlagBits::eDepthStencilAttachment
	);
}

bool ScrapEngine::Render::VulkanDepthResources::has_stencil_component(const vk::Format& format)
{
	return format == vk::Format::eD32SfloatS8Uint || format == vk::Format::eD24UnormS8Uint;
}

vk::Image* ScrapEngine::Render::VulkanDepthResources::get_depth_image()
{
	return &depth_image_;
}

vk::ImageView* ScrapEngine::Render::VulkanDepthResources::get_depth_image_view()
{
	return &depth_image_view_;
}
