#pragma once

#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <string>

namespace ScrapEngine
{
	namespace Render
	{
		class SkyboxStagingTexture : public BaseTexture
		{
		private:
			int tex_width_, tex_height_, tex_channels_;

			BaseStagingBuffer* staginf_buffer_ref_ = nullptr;

		public:
			SkyboxStagingTexture(const std::string& file_path);
			~SkyboxStagingTexture();

			BaseStagingBuffer* get_texture_staging_buffer() const override;
			int get_texture_width() const override;
			int get_texture_height() const override;
		};
	}
}
