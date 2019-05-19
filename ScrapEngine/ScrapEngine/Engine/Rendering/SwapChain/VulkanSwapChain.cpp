#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>

#include <algorithm>
#include <Engine/Rendering/Base/StaticTypes.h>

ScrapEngine::Render::VulkanSwapChain::VulkanSwapChain(const SwapChainSupportDetails swap_chain_support, GraphicsQueue::QueueFamilyIndices indices, vk::SurfaceKHR* input_surface_ref, const uint32_t& width, const uint32_t& height, bool vsync)
	: surface_ref_(input_surface_ref)
{
	const vk::SurfaceFormatKHR surface_format = choose_swap_surface_format(swap_chain_support.formats);
	const vk::PresentModeKHR present_mode = choose_swap_present_mode(swap_chain_support.present_modes, vsync);
	const vk::Extent2D extent = choose_swap_extent(swap_chain_support.capabilities, width, height);

	uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;
	if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount) {
		image_count = swap_chain_support.capabilities.maxImageCount;
	}

	vk::SwapchainCreateInfoKHR create_info(
		vk::SwapchainCreateFlagsKHR(),
		*surface_ref_,
		image_count,
		surface_format.format,
		surface_format.colorSpace,
		extent,
		1,
		vk::ImageUsageFlagBits::eColorAttachment
	);

	uint32_t queue_family_indices[] = { static_cast<uint32_t>(indices.graphics_family), static_cast<uint32_t>(indices.present_family) };

	if (indices.graphics_family != indices.present_family) {
		create_info.setImageSharingMode(vk::SharingMode::eConcurrent);
		create_info.setQueueFamilyIndexCount(2);
		create_info.setPQueueFamilyIndices(queue_family_indices);
	}
	else {
		create_info.setImageSharingMode(vk::SharingMode::eExclusive);
	}

	create_info.setPreTransform(swap_chain_support.capabilities.currentTransform);
	create_info.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
	create_info.setPresentMode(present_mode);
	create_info.setClipped(true);

	if (VulkanDevice::static_logic_device_ref->createSwapchainKHR(&create_info, nullptr, &swap_chain_) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanSwapChain: Failed to create swap chain!");
	}

	VulkanDevice::static_logic_device_ref->getSwapchainImagesKHR(swap_chain_, &image_count, nullptr);
	swap_chain_images_.resize(image_count);
	VulkanDevice::static_logic_device_ref->getSwapchainImagesKHR(swap_chain_, &image_count, swap_chain_images_.data());

	swap_chain_image_format_ = surface_format.format;
	swap_chain_extent_ = extent;
}

ScrapEngine::Render::VulkanSwapChain::~VulkanSwapChain()
{
	VulkanDevice::static_logic_device_ref->destroySwapchainKHR(swap_chain_);
}

vk::SurfaceFormatKHR ScrapEngine::Render::VulkanSwapChain::choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& available_formats)
{
	if (available_formats.size() == 1 && available_formats[0].format == vk::Format::eUndefined) {
		return { vk::Format::eB8G8R8A8Unorm , vk::ColorSpaceKHR::eSrgbNonlinear};
	}

	for (const auto& available_format : available_formats) {
		if (available_format.format == vk::Format::eB8G8R8A8Unorm  && available_format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
			return available_format;
		}
	}

	return available_formats[0];
}

vk::PresentModeKHR ScrapEngine::Render::VulkanSwapChain::choose_swap_present_mode(const std::vector<vk::PresentModeKHR>& available_present_modes, bool vsync)
{
	vk::PresentModeKHR best_mode = vk::PresentModeKHR::eFifo;

	for (const auto& available_present_mode : available_present_modes) {
		if (vsync && (available_present_mode == vk::PresentModeKHR::eFifoRelaxed || available_present_mode == vk::PresentModeKHR::eFifo)) {
			return available_present_mode;
		}
		if (available_present_mode == vk::PresentModeKHR::eMailbox) {
			return available_present_mode;
		}
		else if (available_present_mode == vk::PresentModeKHR::eImmediate) {
			best_mode = available_present_mode;
		}
	}

	return best_mode;
}

vk::Extent2D ScrapEngine::Render::VulkanSwapChain::choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities, const uint32_t& width, const uint32_t& height) const
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actual_extent = { width, height };

		actual_extent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actual_extent.width));
		actual_extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actual_extent.height));

		return actual_extent;
	}
}

vk::SwapchainKHR ScrapEngine::Render::VulkanSwapChain::get_swap_chain() const
{
	return swap_chain_;
}

const std::vector<vk::Image>* ScrapEngine::Render::VulkanSwapChain::get_swap_chain_images_vector() const
{
	return &swap_chain_images_;
}

vk::Format ScrapEngine::Render::VulkanSwapChain::get_swap_chain_image_format() const
{
	return swap_chain_image_format_;
}

vk::Extent2D ScrapEngine::Render::VulkanSwapChain::get_swap_chain_extent() const
{
	return swap_chain_extent_;
}
