#include "AnotherTestGameObject.h"
#include <Engine/Debug/DebugLog.h>

AnotherTestGameObject::AnotherTestGameObject(ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	set_object_location(ScrapEngine::Core::SVector3(0, 0, 0));
	set_object_rotation(ScrapEngine::Core::SVector3(0, 0, 0));
	set_object_scale(ScrapEngine::Core::SVector3(0.5f, 0.5f, 0.5f));

	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleGreenTexture.png" }
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleGreenTexture.png" }
	));

	(*get_components())[0]->set_component_location(ScrapEngine::Core::SVector3(0, 0, -10));
	(*get_components())[1]->set_component_location(ScrapEngine::Core::SVector3(0, 0, 10));
}

void AnotherTestGameObject::game_start()
{
}

void AnotherTestGameObject::game_update(float time)
{
}
