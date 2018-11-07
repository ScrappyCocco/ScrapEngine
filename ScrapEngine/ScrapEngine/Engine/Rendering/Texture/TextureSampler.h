#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {

	class TextureSampler
	{
	private:
		vk::Sampler textureSampler;

		vk::Device* deviceRef;
	public:
		TextureSampler(vk::Device* input_deviceRef, uint32_t mipLevels);

		TextureSampler(vk::Device* input_deviceRef, uint32_t mipLevels, vk::Filter magFilter, vk::Filter minFilter,
			vk::SamplerMipmapMode minimapMode = vk::SamplerMipmapMode::eLinear,
			vk::SamplerAddressMode addressModeU = vk::SamplerAddressMode::eRepeat,
			vk::SamplerAddressMode addressModeV = vk::SamplerAddressMode::eRepeat,
			vk::SamplerAddressMode addressModeW = vk::SamplerAddressMode::eRepeat,
			bool compareEnabled = false, vk::CompareOp compareOp = vk::CompareOp::eNever, bool anisotropyEnable = true, uint16_t maxAnisotropy = 16,
			vk::BorderColor borderColor = vk::BorderColor::eFloatTransparentBlack);

		~TextureSampler();

		vk::Sampler* getTextureSampler();
	};

}

