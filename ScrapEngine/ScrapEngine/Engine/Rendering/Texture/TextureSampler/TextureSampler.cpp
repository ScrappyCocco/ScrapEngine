#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::TextureSampler::TextureSampler(const uint32_t& mip_levels)
	: TextureSampler(mip_levels, vk::Filter::eLinear, vk::Filter::eLinear,
	                 vk::SamplerMipmapMode::eLinear, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat,
	                 vk::SamplerAddressMode::eRepeat,
	                 false, vk::CompareOp::eAlways, true, 16)
{
}

ScrapEngine::Render::TextureSampler::TextureSampler(const uint32_t& mip_levels, const vk::Filter mag_filter,
                                                    const vk::Filter min_filter,
                                                    const vk::SamplerMipmapMode minimap_mode,
                                                    const vk::SamplerAddressMode address_mode_u,
                                                    const vk::SamplerAddressMode address_mode_v,
                                                    const vk::SamplerAddressMode address_mode_w,
                                                    const bool compare_enabled,
                                                    const vk::CompareOp compare_op,
                                                    const bool anisotropy_enable, const uint16_t max_anisotropy,
                                                    const vk::BorderColor border_color)
{
	const vk::SamplerCreateInfo sampler_info(
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

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createSampler(&sampler_info, nullptr, &texture_sampler_);

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "TextureSampler: Failed to create texture sampler!");
	}
}

ScrapEngine::Render::TextureSampler::~TextureSampler()
{
	VulkanDevice::get_instance()->get_logical_device()->destroySampler(texture_sampler_);
}

vk::Sampler* ScrapEngine::Render::TextureSampler::get_texture_sampler()
{
	return &texture_sampler_;
}
