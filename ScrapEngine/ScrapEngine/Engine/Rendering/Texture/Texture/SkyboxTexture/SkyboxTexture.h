#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include <vector>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>

namespace ScrapEngine
{
	namespace Render
	{
		class SkyboxTexture : public BaseTexture
		{
		private:
			std::vector<ScrapEngine::Render::BaseTexture*> images_;

			int cube_image_size;
		public:
			SkyboxTexture(const std::array<std::string, 6>& files_path);
			~SkyboxTexture();

			void delete_temporary_images();

			ScrapEngine::Render::BaseStagingBuffer* get_texture_staging_buffer() const override;
			int get_texture_width() const override;
			int get_texture_height() const override;
		};
	}
}