#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace ScrapEngine {
	class GameWindow
	{
	private:
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		const std::string window_title = "ScrapEngine Game";

		GLFWwindow* window; //actual window reference
		
	public:
		GameWindow(uint32_t input_WIDTH = 800, uint32_t input_HEIGHT = 600, std::string input_window_title = "ScrapEngine Game");
		~GameWindow();

		void initializeWindow();

		void setWindowSize(int input_WIDTH, int input_HEIGHT);
		void setWindowTitle(const std::string& title);
		GLFWimage loadIcon(const std::string& path_to_file) const;
		void setWindowIcon(const int& number_of_images, GLFWimage* images) const;

		GLFWwindow* getWindowRef() const;
		bool checkWindowShouldClose() const;
	};

}

