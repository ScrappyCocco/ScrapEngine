#include "GameCamera.h"
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/KeyboardKeys.h>

GameCamera::GameCamera(ScrapEngine::Input::InputManager* CreatedInputManagerf, ScrapEngine::Render::Camera* input_GameCameraRef, TestGameObject* input_GameObjectRef) :
	SGameObject("Camera-Controller Object"), GameCameraRef(input_GameCameraRef), InputManagerRef(CreatedInputManagerf), GameObjectRef(input_GameObjectRef)
{
	GameCameraRef->set_max_render_distance(10000);
}

void GameCamera::game_start()
{

}

void GameCamera::game_update(float time)
{
	const ScrapEngine::Input::mouse_location mouse = InputManagerRef->get_last_mouse_location();

	const ScrapEngine::Input::scroll_status scroll = InputManagerRef->get_mouse_scroll_status();
	if (scroll == ScrapEngine::Input::scroll_status::scroll_up)
	{
		camera_multiplier_++;
	}else if (scroll == ScrapEngine::Input::scroll_status::scroll_down)
	{
		camera_multiplier_--;
	}
	
	GameCameraRef->process_mouse_movement(static_cast<float>(mouse.xpos), static_cast<float>(mouse.ypos), true);

	camera_speed_ = camera_multiplier_ * time;
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_W)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() + (camera_speed_ * GameCameraRef->get_camera_front()));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_S)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() - (camera_speed_ * GameCameraRef->get_camera_front()));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_D)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() + (camera_speed_ * (glm::normalize(glm::cross(GameCameraRef->get_camera_front(), GameCameraRef->get_camera_up())))));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_A)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() - (camera_speed_ * (glm::normalize(glm::cross(GameCameraRef->get_camera_front(), GameCameraRef->get_camera_up())))));
	}

	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_UP)) {
		GameObjectRef->set_object_location(GameObjectRef->get_object_location() + glm::vec3(0, 0, 0.5f));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_DOWN)) {
		GameObjectRef->set_object_location(GameObjectRef->get_object_location() + glm::vec3(0, 0, -0.5f));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_LEFT)) {
		GameObjectRef->set_object_location(GameObjectRef->get_object_location() + glm::vec3(0, 0.5f, 0));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_RIGHT)) {
		GameObjectRef->set_object_location(GameObjectRef->get_object_location() + glm::vec3(0, -0.5f, 0));
	}
}

