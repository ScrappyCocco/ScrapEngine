#include "ShaderManager.h"

ScrapEngine::ShaderManager::ShaderManager(vk::Device* input_deviceRef)
	: deviceRef(input_deviceRef)
{

}

ScrapEngine::ShaderManager::~ShaderManager()
{
}

vk::ShaderModule ScrapEngine::ShaderManager::createShaderModule(const std::vector<char>& code)
{
	vk::ShaderModuleCreateInfo createInfo(
		vk::ShaderModuleCreateFlags(), 
		code.size(), 
		reinterpret_cast<const uint32_t*>(code.data())
	);

	vk::ShaderModule shaderModule;
	if (deviceRef->createShaderModule(&createInfo, nullptr, &shaderModule) != vk::Result::eSuccess) {
		throw std::runtime_error("Failed to create shader module!");
	}

	return shaderModule;
}

std::vector<char> ScrapEngine::ShaderManager::readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file " + filename + "!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}
