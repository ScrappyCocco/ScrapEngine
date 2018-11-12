#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <fstream>

namespace ScrapEngine {

	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		vk::ShaderModule createShaderModule(const std::vector<char>& code);

		static std::vector<char> readFile(const std::string& filename);
	};

}

