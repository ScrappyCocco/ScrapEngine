#define STB_IMAGE_IMPLEMENTATION
#include "TextureImage.h"

#include <stdexcept>
#include "../Memory/MemoryManager.h"
#include "../Buffer/BaseBuffer.h"
#include "../DepthResources/VulkanDepthResources.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "TextureImageView.h"

ScrapEngine::Render::TextureImage::TextureImage(const std::string& file_path, bool shouldCopyFromStaging)
{
	stbi_uc* pixels = stbi_load(file_path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

	vk::DeviceSize imageSize = texWidth * texHeight * 4;
	mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

	if (!pixels) {
		throw std::runtime_error("TextureImage: Failed to load texture image! (pixels not valid) - " + file_path);
	}

	StaginfBufferRef = new StagingBuffer(imageSize, pixels);

	stbi_image_free(pixels);

	createImage(texWidth, texHeight, vk::Format::eR8G8B8A8Unorm, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, vk::MemoryPropertyFlagBits::eDeviceLocal, textureImage, textureImageMemory);

	transitionImageLayout(&textureImage, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal);

	if(shouldCopyFromStaging){
		StagingBuffer::copy_buffer_to_image(StaginfBufferRef->get_staging_buffer(), &textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

		delete StaginfBufferRef;
		StaginfBufferRef = nullptr;

		generateMipmaps(&textureImage, vk::Format::eR8G8B8A8Unorm, texWidth, texHeight, mipLevels);
	}
}

ScrapEngine::Render::TextureImage::~TextureImage()
{
	if (StaginfBufferRef) {
		delete StaginfBufferRef;
	}
	VulkanDevice::static_logic_device_ref->destroyImage(textureImage);
	VulkanDevice::static_logic_device_ref->freeMemory(textureImageMemory);
}

void ScrapEngine::Render::TextureImage::createImage(const uint32_t& width, const uint32_t& height, const vk::Format& format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory)
{
	createImage(width, height, format, tiling, usage, properties, image, imageMemory, mipLevels, vk::SampleCountFlagBits::e1);
}

void ScrapEngine::Render::TextureImage::createImage(const uint32_t& width, const uint32_t& height, const vk::Format& format, vk::ImageTiling tiling, vk::ImageUsageFlags usage,
	vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory, uint32_t mipLevelsData, vk::SampleCountFlagBits numSamples)
{
	vk::ImageCreateInfo imageInfo(
		vk::ImageCreateFlags(), 
		vk::ImageType::e2D, 
		format, 
		vk::Extent3D(width, height, 1), 
		mipLevelsData, 
		1, 
		numSamples, 
		tiling, 
		usage, 
		vk::SharingMode::eExclusive
	);

	if (VulkanDevice::static_logic_device_ref->createImage(&imageInfo, nullptr, &image) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to create image!");
	}

	vk::MemoryRequirements memRequirements;
	VulkanDevice::static_logic_device_ref->getImageMemoryRequirements(image, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(
		memRequirements.size, 
		findMemoryType(memRequirements.memoryTypeBits, properties)
	);

	if (VulkanDevice::static_logic_device_ref->allocateMemory(&allocInfo, nullptr, &imageMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to allocate image memory!");
	}

	VulkanDevice::static_logic_device_ref->bindImageMemory(image, imageMemory, 0);
}

void ScrapEngine::Render::TextureImage::transitionImageLayout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& oldLayout, const vk::ImageLayout& newLayout)
{
	transitionImageLayout(image, format, oldLayout, newLayout, mipLevels);
}

void ScrapEngine::Render::TextureImage::transitionImageLayout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& oldLayout, const vk::ImageLayout& newLayout, const uint32_t& mipLevelsData, int layercount)
{
	vk::CommandBuffer* commandBuffer = BaseBuffer::begin_single_time_commands();

	vk::ImageMemoryBarrier barrier(vk::AccessFlags(), vk::AccessFlags(), oldLayout, newLayout, 0, 0, *image);

	if (newLayout == vk::ImageLayout::eDepthStencilAttachmentOptimal) {
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;

		if (VulkanDepthResources::has_stencil_component(format)) {
			barrier.subresourceRange.aspectMask |= vk::ImageAspectFlagBits::eStencil;
		}
	}
	else {
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
	}

	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = mipLevelsData;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = layercount;

	vk::PipelineStageFlags sourceStage;
	vk::PipelineStageFlags destinationStage;

	if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal) {
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

		sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
		destinationStage = vk::PipelineStageFlagBits::eTransfer;
	}
	else if (oldLayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal) {
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

		sourceStage = vk::PipelineStageFlagBits::eTransfer;
		destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
	}
	else if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eDepthStencilAttachmentOptimal) {
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::eDepthStencilAttachmentWrite;

		sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
		destinationStage = vk::PipelineStageFlagBits::eEarlyFragmentTests;
	}
	else if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eColorAttachmentOptimal) {
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;
		sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
		destinationStage = vk::PipelineStageFlagBits::eColorAttachmentOutput;
	}
	else {
		throw std::invalid_argument("unsupported layout transition!");
	}

	commandBuffer->pipelineBarrier(
		sourceStage, 
		destinationStage, 
		vk::DependencyFlags(), 
		0, nullptr, 
		0, nullptr, 
		1, &barrier
	);

	BaseBuffer::end_single_time_commands(commandBuffer);
}

void ScrapEngine::Render::TextureImage::generateMipmaps(vk::Image* image, const vk::Format& imageFormat, const int32_t& texWidth, const int32_t& texHeight, const uint32_t& mipLevels)
{
	// Check if image format supports linear blitting
	vk::FormatProperties formatProperties = VulkanDevice::static_physical_device_ref->getFormatProperties(imageFormat);

	if (!(formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eSampledImageFilterLinear)) {
		throw std::runtime_error("TextureImage: Texture image format does not support linear blitting!");
	}

	vk::CommandBuffer* commandBuffer = BaseBuffer::begin_single_time_commands();

	vk::ImageMemoryBarrier barrier(
		vk::AccessFlags(), 
		vk::AccessFlags(), 
		vk::ImageLayout::eUndefined, 
		vk::ImageLayout::eUndefined, 
		0, 
		0, 
		*image, 
		vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1)
	);

	int32_t mipWidth = texWidth;
	int32_t mipHeight = texHeight;

	for (uint32_t i = 1; i < mipLevels; i++) {
		barrier.subresourceRange.baseMipLevel = i - 1;
		barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		barrier.newLayout = vk::ImageLayout::eTransferSrcOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;

		commandBuffer->pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer, 
			vk::PipelineStageFlagBits::eTransfer, 
			vk::DependencyFlags(), 
			0, nullptr, 
			0, nullptr, 
			1, &barrier);
		vk::ImageBlit blit(
			vk::ImageSubresourceLayers(
				vk::ImageAspectFlagBits::eColor,
				i - 1,
				0,
				1),
			std::array<vk::Offset3D, 2>{
				vk::Offset3D(),
				vk::Offset3D(mipWidth, mipHeight, 1)
			},
			vk::ImageSubresourceLayers(
				vk::ImageAspectFlagBits::eColor,
				i,
				0,
				1),
				std::array<vk::Offset3D, 2>{
					vk::Offset3D(),
					vk::Offset3D(mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1)
			}
		);

		commandBuffer->blitImage(*image, vk::ImageLayout::eTransferSrcOptimal, *image, vk::ImageLayout::eTransferDstOptimal, 1, &blit, vk::Filter::eLinear);

		barrier.oldLayout = vk::ImageLayout::eTransferSrcOptimal;
		barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

		commandBuffer->pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &barrier);

		if (mipWidth > 1) mipWidth /= 2;
		if (mipHeight > 1) mipHeight /= 2;
	}

	barrier.subresourceRange.baseMipLevel = mipLevels - 1;
	barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
	barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
	barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

	commandBuffer->pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &barrier);

	BaseBuffer::end_single_time_commands(commandBuffer);
}

vk::Image* ScrapEngine::Render::TextureImage::getTextureImage()
{
	return &textureImage;
}

ScrapEngine::Render::StagingBuffer* ScrapEngine::Render::TextureImage::getTextureStagingBuffer()
{
	return StaginfBufferRef;
}

vk::DeviceMemory* ScrapEngine::Render::TextureImage::getTextureImageMemory()
{
	return &textureImageMemory;
}

uint32_t ScrapEngine::Render::TextureImage::getMipLevels() const
{
	return mipLevels;
}

int ScrapEngine::Render::TextureImage::getTextureWidth() const
{
	return texWidth;
}

int ScrapEngine::Render::TextureImage::getTextureHeight() const
{
	return texHeight;
}

int ScrapEngine::Render::TextureImage::getTextureChannels() const
{
	return texChannels;
}

