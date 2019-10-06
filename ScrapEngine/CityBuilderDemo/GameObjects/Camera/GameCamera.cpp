#include "GameCamera.h"
#include <Engine/Input/KeyboardKeys.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/MouseButtons.h>

GameCamera::GameCamera(ScrapEngine::Input::InputManager* created_input_manager,
                       ScrapEngine::Render::Camera* input_game_camera_ref)
	: SGameObject("Camera-Controller Object"), game_camera_ref_(input_game_camera_ref),
	  input_manager_ref_(created_input_manager)
{
	game_camera_ref_->set_max_render_distance(static_cast<float>(INT_MAX));
}

void GameCamera::set_raycast_manager(RaycastManager* raycast_manager_ref)
{
	raycast_manager_ = raycast_manager_ref;
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
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_Q))
	{
		game_camera_ref_->set_camera_location(
			game_camera_ref_->get_camera_location() + ScrapEngine::Core::SVector3(0, 1, 0) * camera_speed_);
	}
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_E))
	{
		game_camera_ref_->set_camera_location(
			game_camera_ref_->get_camera_location() + ScrapEngine::Core::SVector3(0, -1, 0) * camera_speed_);
	}

	const ScrapEngine::Input::mouse_location mouse = input_manager_ref_->get_last_mouse_location();
	raycast_manager_->mouse_movement(mouse.xpos, mouse.ypos);

	if (input_manager_ref_->get_mouse_button_pressed(MOUSE_BUTTON_LEFT) && click_only_)
	{
		ScrapEngine::Debug::DebugLog::print_to_console_log("Camera Click");
		raycast_manager_->mouse_click(mouse.xpos, mouse.ypos);
		click_only_ = false;
	}else if(!click_only_ && input_manager_ref_->get_mouse_button_released(MOUSE_BUTTON_LEFT)){
		click_only_ = true;
	}

	//Close game
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ESCAPE))
	{
		ScrapEngine::Debug::DebugLog::print_to_console_log("ESC pressed - leaving game");
		game_window_ref_->close_window();
	}
}
