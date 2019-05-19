#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include "TextureImage.h"
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class TextureImage;
		class StagingBuffer;

		class SkyboxTexture
		{
		private:
			vk::Image cubemap_;
			vk::DeviceMemory cubemap_image_memory_;
			uint32_t mip_levels_;

			std::vector<ScrapEngine::Render::TextureImage*> images_;
		public:
			SkyboxTexture(const std::array<std::string, 6>& files_path);
			~SkyboxTexture();

			void delete_temporary_images();
			vk::Image* get_texture_image();
			uint32_t get_mip_levels() const;
		};
	}
}
