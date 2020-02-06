#include "Ball.h"
#include <Engine/Input/KeyboardKeys.h>
#include <Engine/Input/Manager/InputManager.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/SphereRigidBodyComponent/SphereRigidBodyComponent.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

Ball::Ball(ScrapEngine::Core::ComponentsManager* input_component_manager,
           ScrapEngine::Input::InputManager* created_input_managerf)
	: SGameObject("Ball game object"), component_manager_ref_(input_component_manager),
	  input_manager_ref_(created_input_managerf)
{
	//Add mesh to that GameObject
	set_object_scale(ScrapEngine::Core::SVector3(0.5f, 0.5f, 0.5f));
	set_spawnpoint(ScrapEngine::Core::SVector3(0, -10, 0));

	mesh_ = input_component_manager->create_new_mesh_component(
		"../assets/models/sphere.obj",
		{"../assets/textures/SimpleBallTexture.png"}
	);
	add_component(mesh_);

	collider_ = input_component_manager->create_sphere_rigidbody_component(
		10.f,
		ScrapEngine::Core::SVector3(0, -10, 0), 8.f);
	add_component(collider_);

	collider_->attach_to_mesh(mesh_);

	collider_->set_friction_coefficient(1);
}

void Ball::game_update(const float delta_time)
{
	const int force_to_apply = 700;
	
	if (can_move_)
	{
		if (!is_on_ground())
		{
			return;
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_UP))
		{
			collider_->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, -force_to_apply * (delta_time * 100)));
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_DOWN))
		{
			collider_->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, force_to_apply * (delta_time * 100)));
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_LEFT))
		{
			collider_->apply_force_to_center(ScrapEngine::Core::SVector3(-force_to_apply * (delta_time * 100), 0, 0));
		}
		if (input_manager_ref_->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_RIGHT))
		{
			collider_->apply_force_to_center(ScrapEngine::Core::SVector3(force_to_apply * (delta_time * 100), 0, 0));
		}
	}
}

void Ball::respawn()
{
	collider_->cancel_rigidbody_forces();
	collider_->modify_rigidbody_location(respawn_point_);
}

void Ball::set_can_move(const bool can_move)
{
	can_move_ = can_move;
	if (can_move)
	{
		input_manager_ref_->set_cursor_input_mode(ScrapEngine::Input::cursor_mode::cursor_grabbed_mode);
	}
	else
	{
		input_manager_ref_->set_cursor_input_mode(ScrapEngine::Input::cursor_mode::cursor_normal_mode);
	}
}

bool Ball::get_can_move() const
{
	return can_move_;
}

void Ball::set_spawnpoint(const ScrapEngine::Core::SVector3& pos)
{
	respawn_point_ = pos;
}

ScrapEngine::Core::SVector3 Ball::get_rigidbody_location() const
{
	return mesh_->get_component_location();
}

bool Ball::is_on_ground() const
{
	const ScrapEngine::Core::SVector3 start_pos = get_rigidbody_location();
	const ScrapEngine::Core::SVector3 end_pos = start_pos - ScrapEngine::Core::SVector3(0, 50, 0);
	const ScrapEngine::Core::raycast_result result = component_manager_ref_->execute_single_raycast(start_pos, end_pos);
	if (result.component_hit) {
		const SGameObject* owner = result.component_hit->get_owner();
		if (owner) {
			const bool is_terrain = owner->to_string() == "Terrain game object";
			const bool is_checkpoint = owner->to_string() == "Checkpoint game object";
			const float distance = std::abs(start_pos.get_y() - result.world_normal.get_y());
			if ((is_terrain || is_checkpoint) && distance < 10.0f) {
				//The standard distance is around 8.5f so <10.f should be good enough
				return true; //The ball is on the ground and can move
			}
		}
	}
	//Not on ground
	return false;
}
