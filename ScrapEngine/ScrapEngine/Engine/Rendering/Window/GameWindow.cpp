#include "GameWindow.h"

ScrapEngine::GameWindow::GameWindow(uint32_t input_WIDTH, uint32_t input_HEIGHT, std::string input_window_title) : WIDTH(input_WIDTH), HEIGHT(input_HEIGHT), window_title(input_window_title)
{
	initializeWindow();
}

ScrapEngine::GameWindow::~GameWindow()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}

void ScrapEngine::GameWindow::initializeWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //initializes the GLFW library
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, window_title.c_str(), nullptr, nullptr); //initialize the window
}

void ScrapEngine::GameWindow::setWindowSize(int input_WIDTH, int input_HEIGHT)
{
	glfwSetWindowSize(window, input_WIDTH, input_HEIGHT);
}

void ScrapEngine::GameWindow::setWindowTitle(std::string title)
{
	glfwSetWindowTitle(window, title.c_str());
}

void ScrapEngine::GameWindow::setWindowIcon(GLFWimage images[2])
{
	glfwSetWindowIcon(window, 2, images);
}

GLFWwindow * ScrapEngine::GameWindow::getWindowRef() const
{
	return window;
}

bool ScrapEngine::GameWindow::checkWindowShouldClose() const
{
	if (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		return false;
	}
	return true;
}
