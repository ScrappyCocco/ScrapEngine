#include "TextureSampler.h"
#include <stdexcept>
#include "../Base/StaticTypes.h"

ScrapEngine::TextureSampler::TextureSampler(const uint32_t& mipLevels)
	: TextureSampler(mipLevels, vk::Filter::eLinear, vk::Filter::eLinear,
		vk::SamplerMipmapMode::eLinear, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat,
		false, vk::CompareOp::eAlways, true, 16)
{ }

ScrapEngine::TextureSampler::TextureSampler(const uint32_t& mipLevels, vk::Filter magFilter, vk::Filter minFilter, vk::SamplerMipmapMode minimapMode,
	vk::SamplerAddressMode addressModeU, vk::SamplerAddressMode addressModeV, vk::SamplerAddressMode addressModeW, bool compareEnabled, vk::CompareOp compareOp,
	bool anisotropyEnable, uint16_t maxAnisotropy, vk::BorderColor borderColor)
{
	vk::SamplerCreateInfo samplerInfo(
		vk::SamplerCreateFlags(),
		magFilter,
		minFilter,
		minimapMode,
		addressModeU,
		addressModeV,
		addressModeW,
		0.f,
		anisotropyEnable,
		maxAnisotropy,
		compareEnabled,
		compareOp,
		0.f,
		static_cast<float>(mipLevels),
		borderColor
	);

	if (VulkanDevice::StaticLogicDeviceRef->createSampler(&samplerInfo, nullptr, &textureSampler) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureSampler: Failed to create texture sampler!");
	}
}

ScrapEngine::TextureSampler::~TextureSampler()
{
	VulkanDevice::StaticLogicDeviceRef->destroySampler(textureSampler);
}

vk::Sampler* ScrapEngine::TextureSampler::getTextureSampler()
{
	return &textureSampler;
}
