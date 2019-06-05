#include "AnotherTestGameObject.h"
#include <Engine/Debug/DebugLog.h>

AnotherTestGameObject::AnotherTestGameObject(ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	set_object_location(ScrapEngine::Core::SVector3(0, -20, 0));
	set_object_rotation(ScrapEngine::Core::SVector3(0, 0, 0));

	ScrapEngine::Core::MeshComponent* mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleWhiteTexture.png" }
	);
	add_component(mesh);
	(*get_components())[0]->set_component_location(ScrapEngine::Core::SVector3(10, 0, 0));
	(*get_components())[0]->set_component_scale(ScrapEngine::Core::SVector3(10, 1, 1));

	ScrapEngine::Core::MeshComponent* mesh2 = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleWhiteTexture.png" }
	);
	add_component(mesh2);
	(*get_components())[1]->set_component_location(ScrapEngine::Core::SVector3(-10, 0, 0));

	/*ScrapEngine::Core::ColliderComponent* collider = input_ComponentManager->create_box_collider_component(
		ScrapEngine::Core::SVector3(25.f, 0.5f, 25.f),
		ScrapEngine::Core::SVector3(0, -20, 0), 0.f);
	add_component(collider);

	collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	collider->attach_to_mesh(mesh);*/
}

void AnotherTestGameObject::game_start()
{
}

void AnotherTestGameObject::game_update(float time)
{
	set_object_rotation(get_object_rotation() + ScrapEngine::Core::SVector3(0, 0, 0.5f));
	//set_object_location(get_object_location() + ScrapEngine::Core::SVector3(0, 0, 0.5f));
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_location());
	//ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_rotation());
}
