#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class TextureImageView
		{
		private:
			vk::ImageView texture_image_view_;
		public:
			TextureImageView(vk::Image* texture_image, const uint32_t& mip_levels_data, bool iscubemap = false,
			                 int layer_count = 1);
			~TextureImageView();

			static vk::ImageView create_image_view(vk::Image* image, vk::Format format,
			                                       const vk::ImageAspectFlags& aspect_flags, uint32_t mip_levels_data);
			static vk::ImageView create_cube_map_image_view(vk::Image* image, vk::Format format,
			                                                const vk::ImageAspectFlags& aspect_flags, uint32_t mip_levels_data,
			                                                int layer_count);
			vk::ImageView* get_texture_image_view();
		};
	}
}
