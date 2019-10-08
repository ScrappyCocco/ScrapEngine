#include "GameCamera.h"
#include <Engine/Input/KeyboardKeys.h>
#include "Engine/Debug/DebugLog.h"

GameCamera::GameCamera(ScrapEngine::Input::InputManager* created_input_managerf,
                       ScrapEngine::Render::Camera* input_game_camera_ref,
                       Ball* player)
	: SGameObject("Camera-Controller Object"), game_camera_ref_(input_game_camera_ref),
	  input_manager_ref_(created_input_managerf), player_ref_(player)
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
	//Free camera switch
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_F) && !free_camera_key_pressed_)
	{
		if (player_ref_->get_can_move())
		{
			free_camera_key_pressed_ = true;
			free_camera_ = !free_camera_;
			if (!free_camera_) //Reset rotation
			{
				game_camera_ref_->set_camera_pitch(-40.f);
				game_camera_ref_->set_camera_yaw(-90);
				game_camera_ref_->set_camera_roll(0);
			}
		}
	}
	if (input_manager_ref_->get_keyboard_key_released(KEYBOARD_KEY_F) && free_camera_key_pressed_)
	{
		free_camera_key_pressed_ = false;
	}

	//Movement with free camera or with the player ball
	if (!free_camera_)
	{
		ScrapEngine::Core::SVector3 player_location = player_ref_->get_rigidbody_location();
		player_location.set_y(player_location.get_y() + 160);
		player_location.set_z(player_location.get_z() + 250);
		game_camera_ref_->set_camera_location(player_location);
	}
	else
	{
		//look position
		const ScrapEngine::Input::mouse_location mouse = input_manager_ref_->get_last_mouse_location();
		game_camera_ref_->process_mouse_movement(static_cast<float>(mouse.xpos), static_cast<float>(mouse.ypos), true);

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
				game_camera_ref_->get_camera_location() + (game_camera_ref_->get_camera_front() * camera_speed_));
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_S))
		{
			game_camera_ref_->set_camera_location(
				game_camera_ref_->get_camera_location() - (game_camera_ref_->get_camera_front() * camera_speed_));
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_D))
		{
			game_camera_ref_->set_camera_location(
				game_camera_ref_->get_camera_location() +
				(
					ScrapEngine::Core::SVector3::cross_product(
						game_camera_ref_->get_camera_front(), game_camera_ref_->get_camera_up()
					).normalize()
					* camera_speed_
				)
			);
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_A))
		{
			game_camera_ref_->set_camera_location(
				game_camera_ref_->get_camera_location() -
				(
					ScrapEngine::Core::SVector3::cross_product(
						game_camera_ref_->get_camera_front(), game_camera_ref_->get_camera_up()
					).normalize()
					* camera_speed_
				)
			);
		}
	}

	//Close game
	if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ESCAPE))
	{
		ScrapEngine::Debug::DebugLog::print_to_console_log("ESC pressed - leaving game");
		game_window_ref_->close_window();
	}
}
