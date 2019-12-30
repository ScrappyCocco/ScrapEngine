#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <string>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>


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
			SkyboxStagingTexture(const std::string& file_path, bool should_copy_from_staging = true);
			~SkyboxStagingTexture();

			BaseStagingBuffer* get_texture_staging_buffer() const override;
			int get_texture_width() const override;
			int get_texture_height() const override;
		};
	}
}
