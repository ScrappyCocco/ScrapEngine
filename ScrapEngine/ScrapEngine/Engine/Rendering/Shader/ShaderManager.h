#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <fstream>

namespace ScrapEngine {

	class ShaderManager
	{
	private:
		VkDevice deviceRef;
	public:
		ShaderManager(VkDevice input_deviceRef);
		~ShaderManager();

		VkShaderModule createShaderModule(const std::vector<char>& code);

		static std::vector<char> readFile(const std::string& filename);
	};

}

