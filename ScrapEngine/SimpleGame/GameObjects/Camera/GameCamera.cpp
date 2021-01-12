#include "GameCamera.h"
#include <Engine/Input/KeyboardKeys.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/LogicCore/Components/CameraComponent/CameraComponent.h>
#include <Engine/Rendering/Window/GameWindow.h>

GameCamera::GameCamera(ScrapEngine::Input::InputManager* created_input_managerf,
                       ScrapEngine::Core::ComponentsManager* components_manager,
                       Ball* player)
	: SGameObject("Camera-Controller Object"),
	  input_manager_ref_(created_input_managerf),
	  player_ref_(player)
{
	camera_component_ = components_manager->get_camera();
	//Use something smaller than INT_MAX that's not necessary
	camera_component_->set_max_render_distance(5000);
	add_component(camera_component_);
}

void GameCamera::set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref)
{
	game_window_ref_ = window_ref;
}

void GameCamera::game_start()
{
	set_object_location(ScrapEngine::Core::SVector3(0.20f, 150.f, 234.f));
	set_object_rotation(ScrapEngine::Core::SVector3(-40.f, -90, 0));
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
				camera_component_->set_component_rotation(ScrapEngine::Core::SVector3(-40.f, -90, 0));
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
		set_object_location(player_location);
	}
	else
	{
		//look position
		const ScrapEngine::Input::mouse_location mouse = input_manager_ref_->get_last_mouse_location();
		camera_component_->process_mouse_movement(static_cast<float>(mouse.xpos), static_cast<float>(mouse.ypos), true);

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
			set_object_location(get_object_location() + camera_component_->get_camera_front() * camera_speed_);
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_S))
		{
			set_object_location(get_object_location() - camera_component_->get_camera_front() * camera_speed_);
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_D))
		{
			set_object_location(get_object_location() +
				(
					ScrapEngine::Core::SVector3::cross_product(camera_component_->get_camera_front(),
					                                           camera_component_->get_camera_up()).normalize() *
					camera_speed_
				)
			);
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_A))
		{
			set_object_location(get_object_location() -
				(
					ScrapEngine::Core::SVector3::cross_product(camera_component_->get_camera_front(),
					                                           camera_component_->get_camera_up()).normalize() *
					camera_speed_
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
