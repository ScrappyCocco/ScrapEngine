#include "ShaderManager.h"
#include "../Base/StaticTypes.h"

vk::ShaderModule ScrapEngine::Render::ShaderManager::createShaderModule(const std::vector<char>& code)
{
	vk::ShaderModuleCreateInfo createInfo(
		vk::ShaderModuleCreateFlags(), 
		code.size(), 
		reinterpret_cast<const uint32_t*>(code.data())
	);

	vk::ShaderModule shaderModule;
	if (VulkanDevice::static_logic_device_ref->createShaderModule(&createInfo, nullptr, &shaderModule) != vk::Result::eSuccess) {
		throw std::runtime_error("ShaderManager: Failed to create shader module!");
	}

	return shaderModule;
}

std::vector<char> ScrapEngine::Render::ShaderManager::readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("ShaderManager: Failed to open file " + filename + "!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}
