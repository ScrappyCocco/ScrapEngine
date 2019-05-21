#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class ShaderManager
		{
		public:
			ShaderManager() = default;
			~ShaderManager() = default;

			static vk::ShaderModule create_shader_module(const std::vector<char>& code);

			static std::vector<char> read_file(const std::string& filename);
		};
	}
}
