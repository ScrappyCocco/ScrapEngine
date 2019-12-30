#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <string>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>


namespace ScrapEngine
{
	namespace Render
	{
		class StandardTexture : public BaseTexture
		{
		private:
			int tex_width_, tex_height_, tex_channels_;
		public:
			StandardTexture(const std::string& file_path, bool should_copy_from_staging = true);
			~StandardTexture();

			void transition_image_layout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& old_layout,
			                             const vk::ImageLayout& new_layout) const;

			int get_texture_width() const override;
			int get_texture_height() const override;
			int get_texture_channels() const;
		};
	}
}
