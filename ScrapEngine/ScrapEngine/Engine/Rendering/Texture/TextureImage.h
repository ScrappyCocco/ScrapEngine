#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include "../Buffer/Staging/StagingBuffer.h"


namespace ScrapEngine {

	class StagingBuffer;

	class TextureImage
	{
	private:
		vk::Image textureImage;
		vk::DeviceMemory textureImageMemory;
		uint32_t mipLevels;
		int texWidth, texHeight, texChannels;

		vk::Device* deviceRef;
		vk::PhysicalDevice* PhysicalDeviceRef;
		vk::CommandPool* CommandPoolRef;
		vk::Queue* graphicsQueueRerf;
		ScrapEngine::StagingBuffer* StaginfBufferRef = nullptr;

	public:
		TextureImage(std::string file_path, vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, bool shouldCopyFromStaging = true);
		~TextureImage();

		void createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory);
		static void createImage(vk::Device* deviceRef, vk::PhysicalDevice* PhysicalDeviceRef, uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, 
			vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory, uint32_t mipLevelsData, vk::SampleCountFlagBits numSamples);
		
		void transitionImageLayout(vk::Image* image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
		static void transitionImageLayout(vk::Device* deviceRef, vk::Image* image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, uint32_t mipLevelsData, int layercount = 1);

		void generateMipmaps(vk::Image* image, vk::Format imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

		vk::Image* getTextureImage();
		ScrapEngine::StagingBuffer* getTextureStagingBuffer();
		vk::DeviceMemory* getTextureImageMemory();
		uint32_t getMipLevels() const;
		int getTextureWidth() const;
		int getTextureHeight() const;
		int getTextureChannels() const;
	};

}

