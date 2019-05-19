#include <Engine/Rendering/Window/GameWindow.h>
#include <stb_image.h>
#include <Engine/Utility/UsefulMethods.h>

ScrapEngine::Render::GameWindow::GameWindow(
	uint32_t input_width, uint32_t input_height, std::string input_window_title)
	: width_(input_width), height_(input_height), window_title_(input_window_title)
{
	initialize_window();
}

ScrapEngine::Render::GameWindow::~GameWindow()
{
	glfwDestroyWindow(window_);

	glfwTerminate();
}

void ScrapEngine::Render::GameWindow::initialize_window()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //initializes the GLFW library
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window_ = glfwCreateWindow(width_, height_, window_title_.c_str(), nullptr, nullptr); //initialize the window
}

void ScrapEngine::Render::GameWindow::set_window_size(int input_width, int input_height) const
{
	glfwSetWindowSize(window_, input_width, input_height);
}

void ScrapEngine::Render::GameWindow::set_window_title(const std::string& title) const
{
	glfwSetWindowTitle(window_, title.c_str());
}

void ScrapEngine::Render::GameWindow::set_window_icon(const std::string& path_to_file) const
{
	glfwSetWindowIcon(window_, 1, &Utility::UsefulMethods::load_icon(path_to_file));
}

void ScrapEngine::Render::GameWindow::close_window() const
{
	glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

ScrapEngine::Input::InputManager* ScrapEngine::Render::GameWindow::create_window_input_manager() const
{
	return new ScrapEngine::Input::InputManager(window_);
}

bool ScrapEngine::Render::GameWindow::check_window_should_close() const
{
	if (!glfwWindowShouldClose(window_))
	{
		glfwPollEvents();
		return false;
	}
	return true;
}
