#include <Engine/Rendering/Window/GameWindow.h>
#include <stb_image.h>
#include <Engine/Utility/UsefulMethods.h>

ScrapEngine::Render::GameWindow::GameWindow(
	const uint32_t input_width, const uint32_t input_height, const std::string& input_window_title)
	: width_(input_width), height_(input_height), window_title_(input_window_title)
{
	initialize_window();

	int monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	GLFWmonitor* best_monitor = monitors[0];
	center_window(best_monitor);
}

ScrapEngine::Render::GameWindow::~GameWindow()
{
	delete input_;

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

void ScrapEngine::Render::GameWindow::center_window(GLFWmonitor* monitor) const
{
	if (!monitor)
		return;

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (!mode)
		return;

	int monitor_x, monitor_y;
	glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

	int window_width, window_height;
	glfwGetWindowSize(window_, &window_width, &window_height);

	glfwSetWindowPos(window_,
	                 monitor_x + (mode->width - window_width) / 2,
	                 monitor_y + (mode->height - window_height) / 2);
}

ScrapEngine::Render::GameWindow::window_pos ScrapEngine::Render::GameWindow::get_window_pos() const
{
	window_pos return_pos{};
	glfwGetWindowPos(window_, &return_pos.xpos, &return_pos.ypos);
	return return_pos;
}

void ScrapEngine::Render::GameWindow::set_window_size(const int input_width, const int input_height) const
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

ScrapEngine::Input::InputManager* ScrapEngine::Render::GameWindow::create_window_input_manager()
{
	if (input_ == nullptr)
	{
		input_ = new Input::InputManager(window_);
	}
	return input_;
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
