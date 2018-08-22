#pragma once

#include <vulkan/vulkan.h>

namespace ScrapEngine {

	class TextureSampler
	{
	private:
		VkSampler textureSampler;

		VkDevice deviceRef;
	public:
		TextureSampler(VkDevice input_deviceRef, uint32_t mipLevels);
		~TextureSampler();

		VkSampler getTextureSampler() const;
	};

}

