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

			vk::ShaderModule create_shader_module(const std::vector<char>& code);

			static std::vector<char> read_file(const std::string& filename);
		};
	}
}

