#include "TextureImageView.h"

#include <stdexcept>

ScrapEngine::TextureImageView::TextureImageView(vk::Device* input_deviceRef, vk::Image* textureImage, uint32_t mipLevelsData, bool iscubemap, int layerCount)
	: deviceRef(input_deviceRef)
{
	if (iscubemap) {
		textureImageView = createCubeMapImageView(deviceRef, textureImage, vk::Format::eR8G8B8A8Unorm, vk::ImageAspectFlagBits::eColor, mipLevelsData, layerCount);
	}
	else {
		textureImageView = createImageView(deviceRef, textureImage, vk::Format::eR8G8B8A8Unorm, vk::ImageAspectFlagBits::eColor, mipLevelsData);
	}
}

ScrapEngine::TextureImageView::~TextureImageView()
{
	deviceRef->destroyImageView(textureImageView);
}

vk::ImageView ScrapEngine::TextureImageView::createImageView(vk::Device* input_deviceRef, vk::Image* image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData) {
	vk::ImageViewCreateInfo viewInfo(
		vk::ImageViewCreateFlags(), 
		*image, 
		vk::ImageViewType::e2D, 
		format, 
		vk::ComponentMapping(),
		vk::ImageSubresourceRange(aspectFlags, 0, mipLevelsData, 0, 1)
	);

	vk::ImageView imageView;
	if (input_deviceRef->createImageView(&viewInfo, nullptr, &imageView) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImageView: Failed to create texture image view!");
	}

	return imageView;
}

vk::ImageView ScrapEngine::TextureImageView::createCubeMapImageView(vk::Device * input_deviceRef, vk::Image * image, vk::Format format, vk::ImageAspectFlags aspectFlags, uint32_t mipLevelsData, int layerCount)
{
	vk::ImageViewCreateInfo viewInfo(
		vk::ImageViewCreateFlags(),
		*image,
		vk::ImageViewType::eCube,
		format,
		vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA),
		vk::ImageSubresourceRange(aspectFlags, 0, mipLevelsData, layerCount)
	);

	vk::ImageView imageView;
	if (input_deviceRef->createImageView(&viewInfo, nullptr, &imageView) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImageView: Failed to create texture image view!");
	}

	return imageView;
}

vk::ImageView* ScrapEngine::TextureImageView::getTextureImageView()
{
	return &textureImageView;
}
