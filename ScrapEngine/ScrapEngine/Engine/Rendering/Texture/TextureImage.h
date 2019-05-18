#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include "Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h"


namespace ScrapEngine {
	namespace Render {
		class StagingBuffer;

		class TextureImage
		{
		private:
			vk::Image textureImage;
			vk::DeviceMemory textureImageMemory;
			uint32_t mipLevels;
			int texWidth, texHeight, texChannels;

			ScrapEngine::Render::StagingBuffer* StaginfBufferRef = nullptr;

		public:
			TextureImage(const std::string& file_path, bool shouldCopyFromStaging = true);
			~TextureImage();

			void createImage(const uint32_t& width, const uint32_t& height, const vk::Format& format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory);
			static void createImage(const uint32_t& width, const uint32_t& height, const vk::Format& format, vk::ImageTiling tiling, vk::ImageUsageFlags usage,
				vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory, uint32_t mipLevelsData, vk::SampleCountFlagBits numSamples);

			void transitionImageLayout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& oldLayout, const vk::ImageLayout& newLayout);
			static void transitionImageLayout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& oldLayout, const vk::ImageLayout& newLayout, const uint32_t& mipLevelsData, int layercount = 1);

			void generateMipmaps(vk::Image* image, const vk::Format& imageFormat, const int32_t& texWidth, const int32_t& texHeight, const uint32_t& mipLevels);

			vk::Image* getTextureImage();
			ScrapEngine::Render::StagingBuffer* getTextureStagingBuffer();
			vk::DeviceMemory* getTextureImageMemory();
			uint32_t getMipLevels() const;
			int getTextureWidth() const;
			int getTextureHeight() const;
			int getTextureChannels() const;
		};
	}
}

