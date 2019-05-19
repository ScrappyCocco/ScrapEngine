#include "InputManager.h"
#include "../../Rendering/Window/GameWindow.h"
#include "../../Utility/UsefulMethods.h"

ScrapEngine::Input::InputManager::InputManager(GLFWwindow* input_window_ref) : window_ref_(input_window_ref)
{
}

ScrapEngine::Input::InputManager::~InputManager()
{
	glfwDestroyCursor(cursor_);
}

ScrapEngine::Input::mouse_location ScrapEngine::Input::InputManager::get_last_mouse_location() const
{
	double x_position, y_position;
	glfwGetCursorPos(window_ref_, &x_position, &y_position);
	return { x_position, y_position };
}

void ScrapEngine::Input::InputManager::set_cursor_input_mode(const ScrapEngine::Input::cursor_mode new_mode) const
{
	switch (new_mode)
	{
	case ScrapEngine::Input::cursor_mode::cursor_normal_mode:
		glfwSetInputMode(window_ref_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case ScrapEngine::Input::cursor_mode::cursor_hidden_mode:
		glfwSetInputMode(window_ref_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case ScrapEngine::Input::cursor_mode::cursor_grabbed_mode:
		glfwSetInputMode(window_ref_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	}
}

void ScrapEngine::Input::InputManager::load_new_cursor(const std::string& path_to_file, const int xhot, const int yhot)
{
	glfwSetCursor(window_ref_, nullptr);
	glfwDestroyCursor(cursor_);

	cursor_ = glfwCreateCursor(&Utility::UsefulMethods::load_icon(path_to_file), xhot, yhot);

	glfwSetCursor(window_ref_, cursor_);
}

void ScrapEngine::Input::InputManager::load_system_cursor(const ScrapEngine::Input::system_cursor_shapes& new_shape)
{
	glfwSetCursor(window_ref_, nullptr);
	glfwDestroyCursor(cursor_);

	switch (new_shape)
	{
	case ScrapEngine::Input::system_cursor_shapes::cursor_regular_arrow:
		cursor_ = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		break;
	case ScrapEngine::Input::system_cursor_shapes::cursor_crosshair_shape:
		cursor_ = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		break;
	case ScrapEngine::Input::system_cursor_shapes::cursor_hand_shape:
		cursor_ = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		break;
	case ScrapEngine::Input::system_cursor_shapes::cursor_horizontal_resize_arrow_shape:
		cursor_ = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		break;
	case ScrapEngine::Input::system_cursor_shapes::cursor_vertical_resize_arrow_shape:
		cursor_ = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		break;
	case ScrapEngine::Input::system_cursor_shapes::cursor_input_beam_shape:
		cursor_ = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		break;
	}

	glfwSetCursor(window_ref_, cursor_);
}

void ScrapEngine::Input::InputManager::reset_cursor_to_system_default()
{
	load_system_cursor(ScrapEngine::Input::system_cursor_shapes::cursor_regular_arrow);
}

ScrapEngine::Input::button_state ScrapEngine::Input::InputManager::get_keyboard_key_status(const int key_to_check) const
{
	return static_cast<ScrapEngine::Input::button_state>(glfwGetKey(window_ref_, key_to_check));
}

bool ScrapEngine::Input::InputManager::get_keyboard_key_pressed(const int key_to_check) const
{
	return get_keyboard_key_status(key_to_check) == ScrapEngine::Input::button_state::pressed;
}

bool ScrapEngine::Input::InputManager::get_keyboard_key_released(const int key_to_check) const
{
	return get_keyboard_key_status(key_to_check) == ScrapEngine::Input::button_state::released;
}

ScrapEngine::Input::button_state ScrapEngine::Input::InputManager::get_mouse_button_status(
	const int button_to_check) const
{
	return static_cast<ScrapEngine::Input::button_state>(glfwGetMouseButton(window_ref_, button_to_check));
}

bool ScrapEngine::Input::InputManager::get_mouse_button_pressed(const int button_to_check) const
{
	return get_mouse_button_status(button_to_check) == ScrapEngine::Input::button_state::pressed;
}

bool ScrapEngine::Input::InputManager::get_mouse_button_released(const int button_to_check) const
{
	return get_mouse_button_status(button_to_check) == ScrapEngine::Input::button_state::released;
}
