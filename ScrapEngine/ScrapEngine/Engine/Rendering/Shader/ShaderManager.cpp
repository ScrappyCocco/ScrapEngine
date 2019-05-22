#include <Engine/Rendering/Shader/ShaderManager.h>
#include <fstream>
#include <Engine/Rendering/Device/VulkanDevice.h>

vk::ShaderModule ScrapEngine::Render::ShaderManager::create_shader_module(const std::vector<char>& code)
{
	vk::ShaderModuleCreateInfo create_info(
		vk::ShaderModuleCreateFlags(),
		code.size(),
		reinterpret_cast<const uint32_t*>(code.data())
	);

	vk::ShaderModule shader_module;
	if (VulkanDevice::get_instance()->get_logical_device()->createShaderModule(&create_info, nullptr, &shader_module)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("ShaderManager: Failed to create shader module!");
	}

	return shader_module;
}

std::vector<char> ScrapEngine::Render::ShaderManager::read_file(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("ShaderManager: Failed to open file " + filename + "!");
	}

	const size_t file_size = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(file_size);
	file.seekg(0);
	file.read(buffer.data(), file_size);
	file.close();

	return buffer;
}
