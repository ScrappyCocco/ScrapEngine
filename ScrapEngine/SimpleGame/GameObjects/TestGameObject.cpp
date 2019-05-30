#include "TestGameObject.h"
#include <Engine/Debug/DebugLog.h>

TestGameObject::TestGameObject(ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	set_object_location(ScrapEngine::Core::SVector3(0, 50, 0));
	set_object_rotation(ScrapEngine::Core::SVector3(0, 0, 0));
	set_object_scale(ScrapEngine::Core::SVector3(0.5f, 0.5f, 0.5f));

	ScrapEngine::Core::MeshComponent* mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleRedTexture.png" }
	);
	add_component(mesh);

	ScrapEngine::Core::ColliderComponent* collider = input_ComponentManager->create_box_collider_component(
		ScrapEngine::Core::SVector3(5.f, 5.f, 5.f),
		ScrapEngine::Core::SVector3(0, 50, 0), 10.f);
	add_component(collider);

	collider->attach_to_mesh(mesh);
}

void TestGameObject::game_start()
{
}

void TestGameObject::game_update(float time)
{
}
