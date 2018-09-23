#define STB_IMAGE_IMPLEMENTATION
#include "TextureImage.h"

#include <stdexcept>
#include "../Memory/MemoryManager.h"
#include "../Buffer/BaseBuffer.h"
#include "../DepthResources/VulkanDepthResources.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "TextureImageView.h"

ScrapEngine::TextureImage::TextureImage(std::string file_path, vk::Device* input_deviceRef, vk::PhysicalDevice* input_PhysicalDeviceRef, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue)
	: deviceRef(input_deviceRef), PhysicalDeviceRef(input_PhysicalDeviceRef), CommandPoolRef(CommandPool), graphicsQueueRerf(graphicsQueue)
{
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(file_path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

	vk::DeviceSize imageSize = texWidth * texHeight * 4;
	mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

	if (!pixels) {
		throw std::runtime_error("Failed to load texture image! (pixels not valid)");
	}

	StaginfBufferRef = new StagingBuffer(deviceRef, PhysicalDeviceRef, &imageSize, pixels);

	stbi_image_free(pixels);

	createImage(texWidth, texHeight, vk::Format::eR8G8B8A8Unorm, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, vk::MemoryPropertyFlagBits::eDeviceLocal, textureImage, textureImageMemory);

	transitionImageLayout(&textureImage, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal);
	StagingBuffer::copyBufferToImage(deviceRef ,StaginfBufferRef->getStagingBuffer(), &textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), CommandPool, graphicsQueue);
	//transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	delete StaginfBufferRef;

	generateMipmaps(&textureImage, vk::Format::eR8G8B8A8Unorm, texWidth, texHeight, mipLevels);
}

ScrapEngine::TextureImage::~TextureImage()
{
	deviceRef->destroyImage(textureImage);
	deviceRef->freeMemory(textureImageMemory);
}

void ScrapEngine::TextureImage::createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory)
{
	createImage(deviceRef, PhysicalDeviceRef, width, height, format, tiling, usage, properties, image, imageMemory, mipLevels, vk::SampleCountFlagBits::e1);
}

void ScrapEngine::TextureImage::createImage(vk::Device* deviceRef, vk::PhysicalDevice* PhysicalDeviceRef, uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage,
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

	if (deviceRef->createImage(&imageInfo, nullptr, &image) != vk::Result::eSuccess) {
		throw std::runtime_error("failed to create image!");
	}

	vk::MemoryRequirements memRequirements;
	deviceRef->getImageMemoryRequirements(image, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(
		memRequirements.size, 
		findMemoryType(memRequirements.memoryTypeBits, properties, PhysicalDeviceRef)
	);

	if (deviceRef->allocateMemory(&allocInfo, nullptr, &imageMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("failed to allocate image memory!");
	}

	deviceRef->bindImageMemory(image, imageMemory, 0);
}

void ScrapEngine::TextureImage::transitionImageLayout(vk::Image* image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout)
{
	transitionImageLayout(deviceRef, image, format, oldLayout, newLayout, CommandPoolRef, graphicsQueueRerf, mipLevels);
}

void ScrapEngine::TextureImage::transitionImageLayout(vk::Device* deviceRef, vk::Image* image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, uint32_t mipLevelsData)
{
	vk::CommandBuffer* commandBuffer = BaseBuffer::beginSingleTimeCommands(deviceRef, CommandPool);

	vk::ImageMemoryBarrier barrier(vk::AccessFlags(), vk::AccessFlags(), oldLayout, newLayout, 0, 0, *image);

	if (newLayout == vk::ImageLayout::eDepthStencilAttachmentOptimal) {
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;

		if (VulkanDepthResources::hasStencilComponent(format)) {
			barrier.subresourceRange.aspectMask |= vk::ImageAspectFlagBits::eStencil;
		}
	}
	else {
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
	}

	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = mipLevelsData;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

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

	BaseBuffer::endSingleTimeCommands(deviceRef, commandBuffer, CommandPool, graphicsQueue);
}

void ScrapEngine::TextureImage::generateMipmaps(vk::Image* image, vk::Format imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels)
{
	// Check if image format supports linear blitting
	vk::FormatProperties formatProperties = PhysicalDeviceRef->getFormatProperties(imageFormat);

	if (!(formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eSampledImageFilterLinear)) {
		throw std::runtime_error("texture image format does not support linear blitting!");
	}

	vk::CommandBuffer* commandBuffer = BaseBuffer::beginSingleTimeCommands(deviceRef, CommandPoolRef);

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

	BaseBuffer::endSingleTimeCommands(deviceRef, commandBuffer, CommandPoolRef, graphicsQueueRerf);
}

vk::Image* ScrapEngine::TextureImage::getTextureImage()
{
	return &textureImage;
}

uint32_t ScrapEngine::TextureImage::getMipLevels() const
{
	return mipLevels;
}

