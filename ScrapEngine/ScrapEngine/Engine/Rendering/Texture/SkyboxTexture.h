#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include "TextureImage.h"
#include <vector>

namespace ScrapEngine {
	namespace Render {
	class TextureImage;
	class StagingBuffer;
	
		class SkyboxTexture
		{
		private:
			vk::Image cubemap;
			vk::DeviceMemory cubemapImageMemory;
			uint32_t mipLevels;

			std::vector<ScrapEngine::Render::TextureImage*> images;
		public:
			SkyboxTexture(const std::array<std::string, 6>& files_path);
			~SkyboxTexture();

			void deleteTemporaryImages();
			vk::Image* getTextureImage();
			uint32_t getMipLevels() const;
		};
	}
}

