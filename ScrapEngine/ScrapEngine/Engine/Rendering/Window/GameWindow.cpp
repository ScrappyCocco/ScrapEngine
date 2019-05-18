#include "GameWindow.h"
#include <stb_image.h>
#include "../../Utility/UsefulMethods.h"

ScrapEngine::Render::GameWindow::GameWindow(uint32_t input_WIDTH, uint32_t input_HEIGHT, std::string input_window_title) : WIDTH(input_WIDTH), HEIGHT(input_HEIGHT), window_title(input_window_title)
{
	initializeWindow();
}

ScrapEngine::Render::GameWindow::~GameWindow()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}

void ScrapEngine::Render::GameWindow::initializeWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //initializes the GLFW library
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, window_title.c_str(), nullptr, nullptr); //initialize the window
}

void ScrapEngine::Render::GameWindow::setWindowSize(int input_WIDTH, int input_HEIGHT)
{
	glfwSetWindowSize(window, input_WIDTH, input_HEIGHT);
}

void ScrapEngine::Render::GameWindow::setWindowTitle(const std::string& title)
{
	glfwSetWindowTitle(window, title.c_str());
}

void ScrapEngine::Render::GameWindow::setWindowIcon(const std::string& path_to_file) const
{
	glfwSetWindowIcon(window, 1, &Utility::UsefulMethods::load_icon(path_to_file));
}

void ScrapEngine::Render::GameWindow::closeWindow()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

ScrapEngine::Input::InputManager* ScrapEngine::Render::GameWindow::createWindowInputManager() const
{
	return new ScrapEngine::Input::InputManager(window);
}

bool ScrapEngine::Render::GameWindow::checkWindowShouldClose() const
{
	if (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		return false;
	}
	return true;
}
