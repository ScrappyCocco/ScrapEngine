#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace ScrapEngine
{
	namespace Utility
	{
		class UsefulMethods
		{
		public:
			static GLFWimage load_icon(const std::string& path_to_file);
		};
	}
}
