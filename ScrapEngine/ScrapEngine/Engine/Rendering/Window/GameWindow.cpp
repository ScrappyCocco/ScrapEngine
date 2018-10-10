#include "GameWindow.h"
#include <stb_image.h>
#include "../../Utility/UsefulMethods.h"

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

void ScrapEngine::GameWindow::setWindowTitle(const std::string& title)
{
	glfwSetWindowTitle(window, title.c_str());
}

void ScrapEngine::GameWindow::setWindowIcon(const std::string& path_to_file) const
{
	glfwSetWindowIcon(window, 1, &UsefulMethods::loadIcon(path_to_file));
}

void ScrapEngine::GameWindow::closeWindow()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

ScrapEngine::InputManager* ScrapEngine::GameWindow::createWindowInputManager() const
{
	return new ScrapEngine::InputManager(window);
}

bool ScrapEngine::GameWindow::checkWindowShouldClose() const
{
	if (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		return false;
	}
	return true;
}
