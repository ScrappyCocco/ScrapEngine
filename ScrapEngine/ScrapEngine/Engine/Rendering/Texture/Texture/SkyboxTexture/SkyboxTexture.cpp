#include <Engine/Rendering/Texture/Texture/SkyboxTexture/SkyboxTexture.h>
#include <Engine/Rendering/Memory/MemoryManager.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>
#include <Engine/Rendering/Texture/Texture/StandardTexture/StandardTexture.h>

ScrapEngine::Render::SkyboxTexture::SkyboxTexture(const std::array<std::string, 6>& files_path)
{
	//-----------------------
	// load images
	//-----------------------
	ScrapEngine::Debug::DebugLog::print_to_console_log("Start loading textures...");

	for (const std::string& file : files_path)
	{
		ScrapEngine::Debug::DebugLog::print_to_console_log("Loading skybox texture:" + file);
		images_.push_back(new StandardTexture(file, false));
		Debug::DebugLog::print_to_console_log("A skybox texture has loaded (" + file + ")");
	}
	cube_image_size = images_.back()->get_texture_height();
	Debug::DebugLog::print_to_console_log("Textures loaded...");
	//-----------------------
	// create cubemap base image
	//-----------------------

	mip_levels_ = static_cast<uint32_t>(std::floor(
		std::log2(std::max(images_[0]->get_texture_width(), images_[0]->get_texture_height())))) + 1;

	vk::ImageCreateInfo image_create_info(
		vk::ImageCreateFlagBits::eCubeCompatible,
		vk::ImageType::e2D,
		vk::Format::eR8G8B8A8Unorm,
		vk::Extent3D(images_[0]->get_texture_width(), images_[0]->get_texture_height(), 1),
		mip_levels_,
		6,
		vk::SampleCountFlagBits::e1,
		vk::ImageTiling::eOptimal,
		vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled,
		vk::SharingMode::eExclusive
	);

	//-----------------------
	// allocate cubemap space memory
	//-----------------------

	if (VulkanDevice::static_logic_device_ref->createImage(&image_create_info, nullptr, &texture_image_) != vk::Result::
		eSuccess)
	{
		throw std::runtime_error("TextureImage: Failed to create image!");
	}

	vk::MemoryRequirements mem_requirements;
	VulkanDevice::static_logic_device_ref->getImageMemoryRequirements(texture_image_, &mem_requirements);

	vk::MemoryAllocateInfo alloc_info(
		mem_requirements.size,
		find_memory_type(mem_requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)
	);

	if (VulkanDevice::static_logic_device_ref->allocateMemory(&alloc_info, nullptr, &texture_image_memory_) != vk::
		Result::eSuccess)
	{
		throw std::runtime_error("TextureImage: Failed to allocate image memory!");
	}

	VulkanDevice::static_logic_device_ref->bindImageMemory(texture_image_, texture_image_memory_, 0);

	//-----------------------
	// copy images
	//-----------------------

	std::vector<vk::BufferImageCopy> buffer_copy_regions;

	for (unsigned int i = 0; i < files_path.size(); ++i)
	{
		vk::BufferImageCopy region(
			0,
			0,
			0,
			vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, i, 1),
			vk::Offset3D(),
			vk::Extent3D(images_[0]->get_texture_width(), images_[0]->get_texture_height(), 1)
		);

		buffer_copy_regions.push_back(region);
	}

	ScrapEngine::Render::BaseTexture::transition_image_layout(&texture_image_, vk::Format::eR8G8B8A8Unorm,
	                                                           vk::ImageLayout::eUndefined,
	                                                           vk::ImageLayout::eTransferDstOptimal, mip_levels_, 6);

	for (unsigned int i = 0; i < buffer_copy_regions.size(); i++)
	{
		ScrapEngine::Render::ImageStagingBuffer::copy_buffer_to_image(
			images_[i]->get_texture_staging_buffer()->get_staging_buffer(), &texture_image_, images_[i]->get_texture_width(),
			images_[i]->get_texture_height(), &buffer_copy_regions[i], 1);
	}

	ScrapEngine::Render::BaseTexture::transition_image_layout(&texture_image_, vk::Format::eR8G8B8A8Unorm,
	                                                           vk::ImageLayout::eTransferDstOptimal,
	                                                           vk::ImageLayout::eShaderReadOnlyOptimal, mip_levels_, 6);

	//Delete all the images since they've been copied
	delete_temporary_images();
}

ScrapEngine::Render::SkyboxTexture::~SkyboxTexture()
{
	//Double-check that the images has been erased
	delete_temporary_images();
}

void ScrapEngine::Render::SkyboxTexture::delete_temporary_images()
{
	for (ScrapEngine::Render::BaseTexture* cube_single_image : images_)
	{
		delete cube_single_image;
	}
	images_.clear();
}

ScrapEngine::Render::BaseStagingBuffer* ScrapEngine::Render::SkyboxTexture::get_texture_staging_buffer() const
{
	return nullptr;
}

int ScrapEngine::Render::SkyboxTexture::get_texture_width() const
{
	return get_texture_height();
}

int ScrapEngine::Render::SkyboxTexture::get_texture_height() const
{
	return cube_image_size;
}
