#include "SkyboxTexture.h"
#include "../Memory/MemoryManager.h"

ScrapEngine::SkyboxTexture::SkyboxTexture(const std::array<std::string, 6>& files_path, vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue)
	: deviceRef(input_deviceRef), PhysicalDeviceRef(PhysicalDevice), CommandPoolRef(CommandPool), graphicsQueueRerf(graphicsQueue)
{
	//-----------------------
	// load images
	//-----------------------
	DebugLog::printToConsoleLog("Start loading textures...");

	for (std::string file : files_path) {
		DebugLog::printToConsoleLog("Loading skybox texture:" + file);
		images.push_back(new TextureImage(file, input_deviceRef, PhysicalDevice, CommandPool, graphicsQueue, false));
		DebugLog::printToConsoleLog("A skybox texture has loaded (" + file + ")");
	}
	DebugLog::printToConsoleLog("Textures loaded...");
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

	if (deviceRef->createImage(&imageCreateInfo, nullptr, &cubemap) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to create image!");
	}

	vk::MemoryRequirements memRequirements;
	deviceRef->getImageMemoryRequirements(cubemap, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(
		memRequirements.size,
		findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, PhysicalDeviceRef)
	);

	if (deviceRef->allocateMemory(&allocInfo, nullptr, &cubemapImageMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to allocate image memory!");
	}

	deviceRef->bindImageMemory(cubemap, cubemapImageMemory, 0);

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

	ScrapEngine::TextureImage::transitionImageLayout(deviceRef, &cubemap, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, CommandPoolRef, graphicsQueue, mipLevels, 6);

	for (int i = 0; i < bufferCopyRegions.size(); i++) {
		ScrapEngine::StagingBuffer::copyBufferToImage(deviceRef, images[i]->getTextureStagingBuffer()->getStagingBuffer(), &cubemap, images[i]->getTextureWidth(), images[i]->getTextureHeight(), CommandPoolRef, graphicsQueue, &bufferCopyRegions[i], 1);
	}

	ScrapEngine::TextureImage::transitionImageLayout(deviceRef, &cubemap, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal, CommandPoolRef, graphicsQueue, mipLevels, 6);
	
	//Delete all the images since they've been copied
	deleteTemporaryImages();
}

ScrapEngine::SkyboxTexture::~SkyboxTexture()
{
	//Double-check that the images has been erased
	deleteTemporaryImages();
	deviceRef->destroyImage(cubemap);
	deviceRef->freeMemory(cubemapImageMemory);
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
