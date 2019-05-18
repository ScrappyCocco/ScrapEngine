#include "TextureImageView.h"

#include <stdexcept>
#include "../Base/StaticTypes.h"

ScrapEngine::Render::TextureImageView::TextureImageView(vk::Image* textureImage, const uint32_t& mipLevelsData, bool iscubemap, int layerCount)
{
	if (iscubemap) {
		textureImageView = createCubeMapImageView(textureImage, vk::Format::eR8G8B8A8Unorm, vk::ImageAspectFlagBits::eColor, mipLevelsData, layerCount);
	}
	else {
		textureImageView = createImageView(textureImage, vk::Format::eR8G8B8A8Unorm, vk::ImageAspectFlagBits::eColor, mipLevelsData);
	}
}

ScrapEngine::Render::TextureImageView::~TextureImageView()
{
	VulkanDevice::StaticLogicDeviceRef->destroyImageView(textureImageView);
}

vk::ImageView ScrapEngine::Render::TextureImageView::createImageView(vk::Image* image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData) {
	vk::ImageViewCreateInfo viewInfo(
		vk::ImageViewCreateFlags(), 
		*image, 
		vk::ImageViewType::e2D, 
		format, 
		vk::ComponentMapping(),
		vk::ImageSubresourceRange(aspectFlags, 0, mipLevelsData, 0, 1)
	);

	vk::ImageView imageView;
	if (ScrapEngine::Render::VulkanDevice::StaticLogicDeviceRef->createImageView(&viewInfo, nullptr, &imageView) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImageView: Failed to create texture image view!");
	}

	return imageView;
}

vk::ImageView ScrapEngine::Render::TextureImageView::createCubeMapImageView(vk::Image* image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData, int layerCount)
{
	vk::ImageViewCreateInfo viewInfo(
		vk::ImageViewCreateFlags(),
		*image,
		vk::ImageViewType::eCube,
		format,
		vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA),
		vk::ImageSubresourceRange(aspectFlags, 0, mipLevelsData, 0, layerCount)
	);

	vk::ImageView imageView;
	if (Render::VulkanDevice::StaticLogicDeviceRef->createImageView(&viewInfo, nullptr, &imageView) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImageView: Failed to create texture image view!");
	}

	return imageView;
}

vk::ImageView* ScrapEngine::Render::TextureImageView::getTextureImageView()
{
	return &textureImageView;
}
