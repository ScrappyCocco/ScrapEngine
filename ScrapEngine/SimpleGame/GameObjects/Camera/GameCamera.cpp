#include "GameCamera.h"
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/KeyboardKeys.h>

GameCamera::GameCamera(ScrapEngine::Input::InputManager* CreatedInputManagerf, ScrapEngine::Render::Camera* input_GameCameraRef) 
:SGameObject("Camera-Controller Object"), GameCameraRef(input_GameCameraRef), InputManagerRef(CreatedInputManagerf)
{
	GameCameraRef->set_max_render_distance(100000);
}

void GameCamera::game_start()
{
	GameCameraRef->set_camera_location(ScrapEngine::Core::SVector3(0.20f, 150.f, 234.f));
	GameCameraRef->set_camera_pitch(-40.f);
}

void GameCamera::game_update(const float time)
{
	//look position
	const ScrapEngine::Input::mouse_location mouse = InputManagerRef->get_last_mouse_location();
	GameCameraRef->process_mouse_movement(static_cast<float>(mouse.xpos), static_cast<float>(mouse.ypos), true);

	//speed
	const ScrapEngine::Input::scroll_status scroll = InputManagerRef->get_mouse_scroll_status();
	if (scroll == ScrapEngine::Input::scroll_status::scroll_up)
	{
		camera_multiplier_++;
	}else if (scroll == ScrapEngine::Input::scroll_status::scroll_down)
	{
		camera_multiplier_--;
	}
	camera_speed_ = camera_multiplier_ * time;

	//Update location
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_W)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() + (GameCameraRef->get_camera_front() * camera_speed_));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_S)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() - (GameCameraRef->get_camera_front() * camera_speed_));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_D)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() + (((GameCameraRef->get_camera_front() ^ GameCameraRef->get_camera_up()).normalize()) * camera_speed_));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_A)) {
		GameCameraRef->set_camera_location(GameCameraRef->get_camera_location() - (((GameCameraRef->get_camera_front() ^ GameCameraRef->get_camera_up()).normalize()) * camera_speed_));
	}
}

