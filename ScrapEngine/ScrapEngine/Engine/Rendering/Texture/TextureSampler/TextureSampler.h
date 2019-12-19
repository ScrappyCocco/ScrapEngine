#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class TextureSampler
		{
		private:
			vk::Sampler texture_sampler_;
		public:
			TextureSampler(const uint32_t& mip_levels);

			TextureSampler(const uint32_t& mip_levels, vk::Filter mag_filter, vk::Filter min_filter,
			               vk::SamplerMipmapMode minimap_mode = vk::SamplerMipmapMode::eLinear,
			               vk::SamplerAddressMode address_mode_u = vk::SamplerAddressMode::eRepeat,
			               vk::SamplerAddressMode address_mode_v = vk::SamplerAddressMode::eRepeat,
			               vk::SamplerAddressMode address_mode_w = vk::SamplerAddressMode::eRepeat,
			               bool compare_enabled = false, vk::CompareOp compare_op = vk::CompareOp::eNever,
			               bool anisotropy_enable = true, uint16_t max_anisotropy = 16,
			               vk::BorderColor border_color = vk::BorderColor::eFloatTransparentBlack);

			~TextureSampler();

			vk::Sampler* get_texture_sampler();
		};
	}
}
