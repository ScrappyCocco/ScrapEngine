#include "GameCamera.h"
#include <Engine/Input/KeyboardKeys.h>
#include "Engine/Debug/DebugLog.h"

GameCamera::GameCamera(ScrapEngine::Input::InputManager* created_input_managerf,
                       ScrapEngine::Render::Camera* input_game_camera_ref)
	: SGameObject("Camera-Controller Object"), game_camera_ref_(input_game_camera_ref),
	  input_manager_ref_(created_input_managerf)
{
	game_camera_ref_->set_max_render_distance(static_cast<float>(INT_MAX));
}

void GameCamera::set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref)
{
	game_window_ref_ = window_ref;
}

void GameCamera::game_start()
{
	game_camera_ref_->set_camera_location(ScrapEngine::Core::SVector3(0.20f, 150.f, 234.f));
	game_camera_ref_->set_camera_pitch(-40.f);
}

void GameCamera::game_update(const float time)
{
	//speed
	const ScrapEngine::Input::scroll_status scroll = input_manager_ref_->get_mouse_scroll_status();
	if (scroll == ScrapEngine::Input::scroll_status::scroll_up)
	{
		camera_multiplier_++;
	}
	else if (scroll == ScrapEngine::Input::scroll_status::scroll_down)
	{
		camera_multiplier_--;
	}
	camera_speed_ = camera_multiplier_ * time;

	//Update location
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_W))
	{
		game_camera_ref_->set_camera_location(
			game_camera_ref_->get_camera_location() + ScrapEngine::Core::SVector3(0, 0, -1) * camera_speed_);
	}
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_S))
	{
		game_camera_ref_->set_camera_location(
			game_camera_ref_->get_camera_location() + ScrapEngine::Core::SVector3(0, 0, 1) * camera_speed_);
	}
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_D))
	{
		game_camera_ref_->set_camera_location(
			game_camera_ref_->get_camera_location() + ScrapEngine::Core::SVector3(1, 0, 0) * camera_speed_);
	}
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_A))
	{
		game_camera_ref_->set_camera_location(
			game_camera_ref_->get_camera_location() + ScrapEngine::Core::SVector3(-1, 0, 0) * camera_speed_);
	}

	//Close game
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ESCAPE))
	{
		ScrapEngine::Debug::DebugLog::print_to_console_log("ESC pressed - leaving game");
		game_window_ref_->close_window();
	}
}
