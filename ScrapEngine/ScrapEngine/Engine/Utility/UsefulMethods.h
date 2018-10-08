#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace ScrapEngine {

	class UsefulMethods
	{
	public:
		static GLFWimage loadIcon(const std::string& path_to_file);
	};

}

