#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/Buffer/StagingBuffer/BaseStagingBuffer.h>


namespace ScrapEngine
{
	namespace Render
	{
		class BaseTexture
		{
		protected:
			vk::Image texture_image_;
			vk::DeviceMemory texture_image_memory_;
			uint32_t mip_levels_;
		public:
			BaseTexture() = default;
			virtual ~BaseTexture() = 0;

			static void create_image(const uint32_t& width, const uint32_t& height, const vk::Format& format,
			                         vk::ImageTiling tiling, const vk::ImageUsageFlags& usage,
			                         const vk::MemoryPropertyFlags& properties, vk::Image& image,
			                         vk::DeviceMemory& image_memory, uint32_t mip_levels_data,
			                         vk::SampleCountFlagBits num_samples);

			static void transition_image_layout(vk::Image* image, const vk::Format& format,
			                                    const vk::ImageLayout& old_layout, const vk::ImageLayout& new_layout,
			                                    const uint32_t& mip_levels_data, int layercount = 1);

			static void generate_mipmaps(vk::Image* image, const vk::Format& image_format, const int32_t& tex_width,
			                             const int32_t& tex_height, const uint32_t& mip_levels);

			vk::Image* get_texture_image();
			vk::DeviceMemory* get_texture_image_memory();
			uint32_t get_mip_levels() const;

			virtual BaseStagingBuffer* get_texture_staging_buffer() const;
			virtual int get_texture_width() const = 0;
			virtual int get_texture_height() const = 0;
		};
	}
}
