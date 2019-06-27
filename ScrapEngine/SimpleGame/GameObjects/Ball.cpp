#include "Ball.h"
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/KeyboardKeys.h>

Ball::Ball(ScrapEngine::Core::ComponentsManager* input_ComponentManager, ScrapEngine::Input::InputManager* CreatedInputManagerf)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager), InputManagerRef(CreatedInputManagerf)
{
	//Add mesh to that GameObject
	set_object_scale(ScrapEngine::Core::SVector3(0.5f, 0.5f, 0.5f));

	ScrapEngine::Core::MeshComponent* mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/sphere.obj",
		{ "../assets/textures/SimpleRedTexture2.png" }
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

void Ball::game_update(float time)
{
	if(InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_UP))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, -500));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_DOWN))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, 500));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_LEFT))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(-500, 0, 0));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_RIGHT))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(500, 0, 0));
	}
}