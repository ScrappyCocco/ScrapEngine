#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <fstream>

namespace ScrapEngine {
	namespace Render {
		class ShaderManager
		{
		public:
			ShaderManager() = default;
			~ShaderManager() = default;

			vk::ShaderModule createShaderModule(const std::vector<char>& code);

			static std::vector<char> readFile(const std::string& filename);
		};
	}
}

