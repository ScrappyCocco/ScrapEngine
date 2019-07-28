#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <unordered_map>

namespace ScrapEngine
{
	namespace Render
	{
		class ShaderManager
		{
		private:
			//Singleton static instance
			static ShaderManager* instance_;

			ShaderManager() = default;

			//Map of already loaded shaders
			std::unordered_map<std::string, vk::ShaderModule> loaded_shaders_;

			static vk::ShaderModule create_shader_module(const std::vector<char>& code);

			static std::vector<char> read_file(const std::string& filename);
		public:
			~ShaderManager();

			void cleanup_shaders();

			//Singleton static function to get or create a class instance
			static ShaderManager* get_instance();

			vk::ShaderModule get_shader_module(const std::string& filename);
		};
	}
}
