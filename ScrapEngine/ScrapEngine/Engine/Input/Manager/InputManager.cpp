#include "InputManager.h"
#include "../../Rendering/Window/GameWindow.h"
#include <stb_image.h>
#include "../../Utility/UsefulMethods.h"

ScrapEngine::InputManager::InputManager(GLFWwindow* input_windowRef) : windowRef(input_windowRef)
{

}

ScrapEngine::InputManager::~InputManager()
{
	glfwDestroyCursor(cursor);
}

ScrapEngine::MouseLocation ScrapEngine::InputManager::getLastMouseLocation() const
{
	double xPosition, yPosition;
	glfwGetCursorPos(windowRef, &xPosition, &yPosition);
	return MouseLocation(xPosition, yPosition);
}

void ScrapEngine::InputManager::SetCursorInputMode(ScrapEngine::CursorMode NewMode) const
{
	switch (NewMode) {
	case ScrapEngine::CursorMode::cursor_normal_mode:
		glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case ScrapEngine::CursorMode::cursor_hidden_mode:
		glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case ScrapEngine::CursorMode::cursor_grabbed_mode:
		glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	}
}

void ScrapEngine::InputManager::LoadNewCursor(const std::string& path_to_file, int xhot, int yhot)
{
	glfwSetCursor(windowRef, NULL);
	glfwDestroyCursor(cursor);

	cursor = glfwCreateCursor(&UsefulMethods::loadIcon(path_to_file), xhot, yhot);

	glfwSetCursor(windowRef, cursor);
}

void ScrapEngine::InputManager::LoadSystemCursor(const ScrapEngine::SystemCursorShapes& NewShape)
{
	glfwSetCursor(windowRef, NULL);
	glfwDestroyCursor(cursor);

	switch (NewShape) {
	case ScrapEngine::SystemCursorShapes::cursor_regular_arrow:
		cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		break;
	case ScrapEngine::SystemCursorShapes::cursor_crosshair_shape:
		cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		break;
	case ScrapEngine::SystemCursorShapes::cursor_hand_shape:
		cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		break;
	case ScrapEngine::SystemCursorShapes::cursor_horizontal_resize_arrow_shape:
		cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		break;
	case ScrapEngine::SystemCursorShapes::cursor_vertical_resize_arrow_shape:
		cursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		break;
	case ScrapEngine::SystemCursorShapes::cursor_input_beam_shape:
		cursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		break;
	}

	glfwSetCursor(windowRef, cursor);
}

void ScrapEngine::InputManager::ResetCursorToSystemDefault()
{
	LoadSystemCursor(ScrapEngine::SystemCursorShapes::cursor_regular_arrow);
}

ScrapEngine::ButtonState ScrapEngine::InputManager::getKeyboardKeyStatus(int key_to_check) const
{
	return (ScrapEngine::ButtonState)glfwGetKey(windowRef, key_to_check);
}

bool ScrapEngine::InputManager::getKeyboardKeyPressed(int key_to_check) const
{
	return getKeyboardKeyStatus(key_to_check) == ScrapEngine::ButtonState::pressed;
}

bool ScrapEngine::InputManager::getKeyboardKeyReleased(int key_to_check) const
{
	return getKeyboardKeyStatus(key_to_check) == ScrapEngine::ButtonState::released;
}

ScrapEngine::ButtonState ScrapEngine::InputManager::getMouseButtonStatus(int button_to_check) const
{
	return (ScrapEngine::ButtonState)glfwGetMouseButton(windowRef, button_to_check);
}

bool ScrapEngine::InputManager::getMouseButtonPressed(int button_to_check) const
{
	return getMouseButtonStatus(button_to_check) == ScrapEngine::ButtonState::pressed;
}

bool ScrapEngine::InputManager::getMouseButtonReleased(int button_to_check) const
{
	return getMouseButtonStatus(button_to_check) == ScrapEngine::ButtonState::released;
}
