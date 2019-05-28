#include "TestGameObject.h"
#include <Engine/Debug/DebugLog.h>

TestGameObject::TestGameObject(ScrapEngine::Input::InputManager* CreatedInputManager, ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), InputManagerRef(CreatedInputManager), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	set_object_location(glm::vec3(0, 0, 0));
	set_object_rotation(glm::vec3(0, 0, 0));
	set_object_scale(glm::vec3(0.5f, 0.5f, 0.5f));

	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleRedTexture.png" }
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleGreenTexture.png" }
	));

	(*get_components())[0]->set_component_location(glm::vec3(0, 0, -10));
	(*get_components())[1]->set_component_location(glm::vec3(0, 0, 10));
}

void TestGameObject::game_start()
{
	set_object_location(glm::vec3(0, 10, 0));
}

void TestGameObject::game_update(float time)
{
	//ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_location());
	//ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_rotation());
}
