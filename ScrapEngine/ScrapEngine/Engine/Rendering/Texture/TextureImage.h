#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include "../Buffer/Staging/StagingBuffer.h"


namespace ScrapEngine {

	class TextureImage
	{
	private:
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		uint32_t mipLevels;

		VkDevice deviceRef;
		VkPhysicalDevice PhysicalDeviceRef;
		VkCommandPool CommandPoolRef;
		VkQueue graphicsQueueRerf;
		ScrapEngine::StagingBuffer* StaginfBufferRef = nullptr;

	public:
		TextureImage(std::string file_path, VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, VkCommandPool CommandPool, VkQueue graphicsQueue);
		~TextureImage();

		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		static void createImage(VkDevice deviceRef, VkPhysicalDevice PhysicalDeviceRef, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, 
			VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, uint32_t mipLevelsData, VkSampleCountFlagBits numSamples);
		
		void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		static void transitionImageLayout(VkDevice deviceRef, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool CommandPool, VkQueue graphicsQueue, uint32_t mipLevelsData);

		void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);


		VkImage getTextureImage() const;
		uint32_t getMipLevels() const;
	};

}

