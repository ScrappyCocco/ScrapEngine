#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseStagingBuffer;
		
		class BaseTexture
		{
		protected:
			vk::Image texture_image_;
			VmaAllocation texture_image_memory_;
			uint32_t mip_levels_;
		public:
			BaseTexture() = default;
			virtual ~BaseTexture() = 0;

			static void transition_image_layout(vk::Image* image, const vk::Format& format,
			                                    const vk::ImageLayout& old_layout, const vk::ImageLayout& new_layout,
			                                    const uint32_t& mip_levels_data, int layercount = 1);

			static void generate_mipmaps(vk::Image* image, const vk::Format& image_format, const int32_t& tex_width,
			                             const int32_t& tex_height, const uint32_t& mip_levels);

			vk::Image* get_texture_image();
			uint32_t get_mip_levels() const;

			virtual BaseStagingBuffer* get_texture_staging_buffer() const;
			virtual int get_texture_width() const = 0;
			virtual int get_texture_height() const = 0;
		};
	}
}
