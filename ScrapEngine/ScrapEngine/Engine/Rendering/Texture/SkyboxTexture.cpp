#include "SkyboxTexture.h"
#include "../Memory/MemoryManager.h"
#include "Engine/Debug/DebugLog.h"

ScrapEngine::Render::SkyboxTexture::SkyboxTexture(const std::array<std::string, 6>& files_path)
{
	//-----------------------
	// load images
	//-----------------------
	ScrapEngine::Debug::DebugLog::print_to_console_log("Start loading textures...");

	for (std::string file : files_path) {
		ScrapEngine::Debug::DebugLog::print_to_console_log("Loading skybox texture:" + file);
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

	if (VulkanDevice::static_logic_device_ref->createImage(&imageCreateInfo, nullptr, &cubemap) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to create image!");
	}

	vk::MemoryRequirements memRequirements;
	VulkanDevice::static_logic_device_ref->getImageMemoryRequirements(cubemap, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(
		memRequirements.size,
		findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)
	);

	if (VulkanDevice::static_logic_device_ref->allocateMemory(&allocInfo, nullptr, &cubemapImageMemory) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureImage: Failed to allocate image memory!");
	}

	VulkanDevice::static_logic_device_ref->bindImageMemory(cubemap, cubemapImageMemory, 0);

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

	ScrapEngine::Render::TextureImage::transitionImageLayout(&cubemap, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, mipLevels, 6);

	for (int i = 0; i < bufferCopyRegions.size(); i++) {
		ScrapEngine::Render::StagingBuffer::copy_buffer_to_image(images[i]->getTextureStagingBuffer()->get_staging_buffer(), &cubemap, images[i]->getTextureWidth(), images[i]->getTextureHeight(), &bufferCopyRegions[i], 1);
	}

	ScrapEngine::Render::TextureImage::transitionImageLayout(&cubemap, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal, mipLevels, 6);
	
	//Delete all the images since they've been copied
	deleteTemporaryImages();
}

ScrapEngine::Render::SkyboxTexture::~SkyboxTexture()
{
	//Double-check that the images has been erased
	deleteTemporaryImages();
	VulkanDevice::static_logic_device_ref->destroyImage(cubemap);
	VulkanDevice::static_logic_device_ref->freeMemory(cubemapImageMemory);
}

void ScrapEngine::Render::SkyboxTexture::deleteTemporaryImages()
{
	for (ScrapEngine::Render::TextureImage* cubeSingleImage : images) {
		delete cubeSingleImage;
	}
	images.clear();
}

vk::Image* ScrapEngine::Render::SkyboxTexture::getTextureImage()
{
	return &cubemap;
}

uint32_t ScrapEngine::Render::SkyboxTexture::getMipLevels() const
{
	return mipLevels;
}
