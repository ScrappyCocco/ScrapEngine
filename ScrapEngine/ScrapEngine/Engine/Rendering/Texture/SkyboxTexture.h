#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include "TextureImage.h"
#include <vector>

namespace ScrapEngine {

	class TextureImage;
	class StagingBuffer;

	class SkyboxTexture
	{
	private:
		vk::Image cubemap;
		vk::DeviceMemory cubemapImageMemory;
		uint32_t mipLevels;

		std::vector<ScrapEngine::TextureImage*> images;

		vk::Device* deviceRef;
		vk::PhysicalDevice* PhysicalDeviceRef;
		vk::CommandPool* CommandPoolRef;
		vk::Queue* graphicsQueueRerf;
	public:
		SkyboxTexture(const std::array<std::string, 6>& files_path, vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue);
		~SkyboxTexture();

		void deleteTemporaryImages();
		vk::Image* getTextureImage();
		uint32_t getMipLevels() const;
	};

}

