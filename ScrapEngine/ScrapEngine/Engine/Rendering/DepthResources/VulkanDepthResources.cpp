#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>

#include <Engine/Rendering/Texture/TextureImage.h>
#include <Engine/Rendering/Texture/TextureImageView.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::VulkanDepthResources::VulkanDepthResources(const vk::Extent2D* swap_chain_extent,
                                                                vk::SampleCountFlagBits msaa_samples)
{
	const vk::Format depth_format = find_depth_format();

	TextureImage::create_image(swap_chain_extent->width, swap_chain_extent->height, depth_format,
	                          vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eDepthStencilAttachment,
	                          vk::MemoryPropertyFlagBits::eDeviceLocal, depth_image_, depth_image_memory_, 1,
	                          msaa_samples);
	depth_image_view_ = TextureImageView::create_image_view(&depth_image_, depth_format, vk::ImageAspectFlagBits::eDepth,
	                                                      1);

	TextureImage::transition_image_layout(&depth_image_, depth_format, vk::ImageLayout::eUndefined,
	                                    vk::ImageLayout::eDepthStencilAttachmentOptimal, 1);
}


ScrapEngine::Render::VulkanDepthResources::~VulkanDepthResources()
{
	VulkanDevice::static_logic_device_ref->destroyImageView(depth_image_view_);
	VulkanDevice::static_logic_device_ref->destroyImage(depth_image_);
	VulkanDevice::static_logic_device_ref->freeMemory(depth_image_memory_);
}

vk::Format ScrapEngine::Render::VulkanDepthResources::find_supported_format(
	const std::vector<vk::Format>& candidates, const vk::ImageTiling tiling, const vk::FormatFeatureFlags& features)
{
	for (vk::Format format : candidates)
	{
		vk::FormatProperties props;
		VulkanDevice::static_physical_device_ref->getFormatProperties(format, &props);

		if (tiling == vk::ImageTiling::eLinear && (props.linearTilingFeatures & features) == features)
		{
			return format;
		}
		else if (tiling == vk::ImageTiling::eOptimal && (props.optimalTilingFeatures & features) == features)
		{
			return format;
		}
	}

	throw std::runtime_error("VulkanDepthResources: Failed to find supported format!");
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

vk::DeviceMemory* ScrapEngine::Render::VulkanDepthResources::get_depth_image_memory()
{
	return &depth_image_memory_;
}

vk::ImageView* ScrapEngine::Render::VulkanDepthResources::get_depth_image_view()
{
	return &depth_image_view_;
}
