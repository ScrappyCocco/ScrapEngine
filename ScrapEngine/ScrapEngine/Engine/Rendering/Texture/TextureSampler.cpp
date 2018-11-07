#include "TextureSampler.h"
#include <stdexcept>

ScrapEngine::TextureSampler::TextureSampler(vk::Device* input_deviceRef, uint32_t mipLevels)
	: TextureSampler(input_deviceRef, mipLevels, vk::Filter::eLinear, vk::Filter::eLinear,
		vk::SamplerMipmapMode::eLinear, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat,
		false, vk::CompareOp::eAlways, true, 16)
{ }

ScrapEngine::TextureSampler::TextureSampler(vk::Device* input_deviceRef, uint32_t mipLevels, vk::Filter magFilter, vk::Filter minFilter, vk::SamplerMipmapMode minimapMode,
	vk::SamplerAddressMode addressModeU, vk::SamplerAddressMode addressModeV, vk::SamplerAddressMode addressModeW, bool compareEnabled, vk::CompareOp compareOp,
	bool anisotropyEnable, uint16_t maxAnisotropy, vk::BorderColor borderColor) : deviceRef(input_deviceRef)
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

	if (deviceRef->createSampler(&samplerInfo, nullptr, &textureSampler) != vk::Result::eSuccess) {
		throw std::runtime_error("TextureSampler: Failed to create texture sampler!");
	}
}

ScrapEngine::TextureSampler::~TextureSampler()
{
	deviceRef->destroySampler(textureSampler);
}

vk::Sampler* ScrapEngine::TextureSampler::getTextureSampler()
{
	return &textureSampler;
}
