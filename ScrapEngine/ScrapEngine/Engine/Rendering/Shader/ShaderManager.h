#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <fstream>

namespace ScrapEngine {

	class ShaderManager
	{
	private:
		vk::Device* deviceRef;
	public:
		ShaderManager(vk::Device* input_deviceRef);
		~ShaderManager();

		vk::ShaderModule createShaderModule(const std::vector<char>& code);

		static std::vector<char> readFile(const std::string& filename);
	};

}

