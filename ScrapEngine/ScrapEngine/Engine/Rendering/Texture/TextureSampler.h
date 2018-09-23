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
		~TextureSampler();

		vk::Sampler* getTextureSampler();
	};

}

