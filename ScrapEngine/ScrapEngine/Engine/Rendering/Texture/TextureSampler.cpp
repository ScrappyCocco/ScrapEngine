#include <Engine/Rendering/Texture/TextureSampler.h>
#include <stdexcept>
#include <Engine/Rendering/Base/StaticTypes.h>

ScrapEngine::Render::TextureSampler::TextureSampler(const uint32_t& mip_levels)
	: TextureSampler(mip_levels, vk::Filter::eLinear, vk::Filter::eLinear,
	                 vk::SamplerMipmapMode::eLinear, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat,
	                 vk::SamplerAddressMode::eRepeat,
	                 false, vk::CompareOp::eAlways, true, 16)
{
}

ScrapEngine::Render::TextureSampler::TextureSampler(const uint32_t& mip_levels, vk::Filter mag_filter,
                                                    vk::Filter min_filter, vk::SamplerMipmapMode minimap_mode,
                                                    vk::SamplerAddressMode address_mode_u,
                                                    vk::SamplerAddressMode address_mode_v,
                                                    vk::SamplerAddressMode address_mode_w, bool compare_enabled,
                                                    vk::CompareOp compare_op,
                                                    bool anisotropy_enable, uint16_t max_anisotropy,
                                                    vk::BorderColor border_color)
{
	vk::SamplerCreateInfo samplerInfo(
		vk::SamplerCreateFlags(),
		mag_filter,
		min_filter,
		minimap_mode,
		address_mode_u,
		address_mode_v,
		address_mode_w,
		0.f,
		anisotropy_enable,
		max_anisotropy,
		compare_enabled,
		compare_op,
		0.f,
		static_cast<float>(mip_levels),
		border_color
	);

	if (VulkanDevice::static_logic_device_ref->createSampler(&samplerInfo, nullptr, &texture_sampler_) != vk::Result::
		eSuccess)
	{
		throw std::runtime_error("TextureSampler: Failed to create texture sampler!");
	}
}

ScrapEngine::Render::TextureSampler::~TextureSampler()
{
	ScrapEngine::Render::VulkanDevice::static_logic_device_ref->destroySampler(texture_sampler_);
}

vk::Sampler* ScrapEngine::Render::TextureSampler::get_texture_sampler()
{
	return &texture_sampler_;
}
