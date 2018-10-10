#include "TextureSampler.h"
#include <stdexcept>

ScrapEngine::TextureSampler::TextureSampler(vk::Device* input_deviceRef, uint32_t mipLevels)
	: deviceRef(input_deviceRef)
{
	vk::SamplerCreateInfo samplerInfo(
		vk::SamplerCreateFlags(), 
		vk::Filter::eLinear, 
		vk::Filter::eLinear, 
		vk::SamplerMipmapMode::eLinear,
		vk::SamplerAddressMode::eRepeat, 
		vk::SamplerAddressMode::eRepeat, 
		vk::SamplerAddressMode::eRepeat, 
		0, 
		true, 
		16, 
		false, 
		vk::CompareOp::eAlways, 
		0, 
		static_cast<float>(mipLevels)
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
