#include "SkyboxTexture.h"
#include "../Memory/MemoryManager.h"

ScrapEngine::SkyboxTexture::SkyboxTexture(const std::array<std::string, 6>& files_path)
{
	//-----------------------
	// load images
	//-----------------------
	Debug::DebugLog::print_to_console_log("Start loading textures...");

	for (std::string file : files_path) {
		Debug::DebugLog::print_to_console_log("Loading skybox texture:" + file);
		images.push_back(new TextureImage(file, false));
		Debug::DebugLog::print_to_console_log("A skybox texture has loaded (" + file + ")");
	}
	Debug::DebugLog::print_to_console_log("Textures loaded...");
	//-----------------------
	// create cubemap base image
	//-----------------------

	mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(images[0]->getTextureWidth(), images[0]->getTextureHeight())))) + 1;
	mipLevels = 1; //Override for testing purpose...

	vk::ImageCreateInfo imageCreateInfo(
		vk::ImageCreateFlagBits::eCubeCompatible,
		vk::ImageType::e2D,
		vk::Format::eR8G8B8A8Unorm,
		vk::Extent3D(images[0]->getTextureWidth(), images[0]->getTextureHeight(), 1),
		mipLevels,
		6,
		vk::SampleCountFlagBits::e1,
		vk::ImageTiling::eOptimal,
		vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled,
		vk::SharingMode::eExclusive
	);

	//-----------------------
	// allocate cubemap space memory
	//-----------------------

	if (VulkanDevice::StaticLogicDeviceRef->createImage(&imageCreateInfo, nullptr, &cubemap) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to create image!");
	}

	vk::MemoryRequirements memRequirements;
	VulkanDevice::StaticLogicDeviceRef->getImageMemoryRequirements(cubemap, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(
		memRequirements.size,
		findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)
	);

	if (VulkanDevice::StaticLogicDeviceRef->allocateMemory(&allocInfo, nullptr, &cubemapImageMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to allocate image memory!");
	}

	VulkanDevice::StaticLogicDeviceRef->bindImageMemory(cubemap, cubemapImageMemory, 0);

	//-----------------------
	// copy images
	//-----------------------

	std::vector<vk::BufferImageCopy> bufferCopyRegions;

	for (int i = 0; i < files_path.size(); ++i) {
		vk::BufferImageCopy region(
			0,
			0,
			0,
			vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, i, 1),
			vk::Offset3D(),
			vk::Extent3D(images[0]->getTextureWidth(), images[0]->getTextureHeight(), 1)
		);

		bufferCopyRegions.push_back(region);

	}

	ScrapEngine::TextureImage::transitionImageLayout(&cubemap, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, mipLevels, 6);

	for (int i = 0; i < bufferCopyRegions.size(); i++) {
		ScrapEngine::StagingBuffer::copyBufferToImage(images[i]->getTextureStagingBuffer()->getStagingBuffer(), &cubemap, images[i]->getTextureWidth(), images[i]->getTextureHeight(), &bufferCopyRegions[i], 1);
	}

	ScrapEngine::TextureImage::transitionImageLayout(&cubemap, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal, mipLevels, 6);
	
	//Delete all the images since they've been copied
	deleteTemporaryImages();
}

ScrapEngine::SkyboxTexture::~SkyboxTexture()
{
	//Double-check that the images has been erased
	deleteTemporaryImages();
	VulkanDevice::StaticLogicDeviceRef->destroyImage(cubemap);
	VulkanDevice::StaticLogicDeviceRef->freeMemory(cubemapImageMemory);
}

void ScrapEngine::SkyboxTexture::deleteTemporaryImages()
{
	for (ScrapEngine::TextureImage* cubeSingleImage : images) {
		delete cubeSingleImage;
	}
	images.clear();
}

vk::Image* ScrapEngine::SkyboxTexture::getTextureImage()
{
	return &cubemap;
}

uint32_t ScrapEngine::SkyboxTexture::getMipLevels() const
{
	return mipLevels;
}
