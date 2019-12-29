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

			BaseStagingBuffer* staginf_buffer_ref_ = nullptr;

		public:
			StandardTexture(const std::string& file_path, bool should_copy_from_staging = true);
			~StandardTexture();

			void create_image(const uint32_t& width, const uint32_t& height, const vk::Format& format,
			                  vk::ImageTiling tiling, const vk::ImageUsageFlags& usage,
			                  const vk::MemoryPropertyFlags& properties,
			                  vk::Image& image, vk::DeviceMemory& image_memory) const;

			void transition_image_layout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& old_layout,
			                             const vk::ImageLayout& new_layout) const;

			BaseStagingBuffer* get_texture_staging_buffer() const override;
			int get_texture_width() const override;
			int get_texture_height() const override;
			int get_texture_channels() const;
		};
	}
}
