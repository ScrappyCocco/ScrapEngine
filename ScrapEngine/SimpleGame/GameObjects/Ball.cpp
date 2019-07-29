#include "Ball.h"
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/KeyboardKeys.h>
#include <imgui.h>

Ball::Ball(ScrapEngine::Core::ComponentsManager* input_ComponentManager, ScrapEngine::Input::InputManager* CreatedInputManagerf)
	: SGameObject("Ball game object"), ComponentManagerRef(input_ComponentManager), InputManagerRef(CreatedInputManagerf)
{
	//Add mesh to that GameObject
	set_object_scale(ScrapEngine::Core::SVector3(0.5f, 0.5f, 0.5f));

	mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/sphere.obj",
		{ "../assets/textures/SimpleBallTexture.png" }
	);
	add_component(mesh);

	collider = input_ComponentManager->create_sphere_rigidbody_component(
		10.f,
		ScrapEngine::Core::SVector3(0, 20, 0), 5.f);
	add_component(collider);

	collider->attach_to_mesh(mesh);

	collider->set_friction_coefficient(1);
}

void Ball::game_start()
{
}

void Ball::game_update(const float delta_time)
{
	if(InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_UP))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, -700 * (delta_time * 100)));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_DOWN))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, 700 * (delta_time * 100)));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_LEFT))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(-700 * (delta_time * 100), 0, 0));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_RIGHT))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(700 * (delta_time * 100), 0, 0));
	}
}
