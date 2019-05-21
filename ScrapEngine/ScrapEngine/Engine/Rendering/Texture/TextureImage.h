#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include <Engine/Rendering/Buffer/StagingBuffer/StagingBuffer.h>


namespace ScrapEngine
{
	namespace Render
	{
		class TextureImage
		{
		private:
			vk::Image texture_image_;
			vk::DeviceMemory texture_image_memory_;
			uint32_t mip_levels_;
			int tex_width_, tex_height_, tex_channels_;

			ScrapEngine::Render::StagingBuffer* staginf_buffer_ref_ = nullptr;

		public:
			TextureImage(const std::string& file_path, bool should_copy_from_staging = true);
			~TextureImage();

			void create_image(const uint32_t& width, const uint32_t& height, const vk::Format& format,
			                  vk::ImageTiling tiling, const vk::ImageUsageFlags& usage,
			                  const vk::MemoryPropertyFlags& properties,
			                  vk::Image& image, vk::DeviceMemory& image_memory) const;
			static void create_image(const uint32_t& width, const uint32_t& height, const vk::Format& format,
			                         vk::ImageTiling tiling, const vk::ImageUsageFlags& usage,
			                         const vk::MemoryPropertyFlags& properties, vk::Image& image,
			                         vk::DeviceMemory& image_memory, uint32_t mip_levels_data,
			                         vk::SampleCountFlagBits num_samples);

			void transition_image_layout(vk::Image* image, const vk::Format& format, const vk::ImageLayout& old_layout,
			                             const vk::ImageLayout& new_layout) const;
			static void transition_image_layout(vk::Image* image, const vk::Format& format,
			                                    const vk::ImageLayout& old_layout, const vk::ImageLayout& new_layout,
			                                    const uint32_t& mip_levels_data, int layercount = 1);

			void generate_mipmaps(vk::Image* image, const vk::Format& image_format, const int32_t& tex_width,
			                      const int32_t& tex_height, const uint32_t& mip_levels);

			vk::Image* get_texture_image();
			ScrapEngine::Render::StagingBuffer* get_texture_staging_buffer() const;
			vk::DeviceMemory* get_texture_image_memory();
			uint32_t get_mip_levels() const;
			int get_texture_width() const;
			int get_texture_height() const;
			int get_texture_channels() const;
		};
	}
}
