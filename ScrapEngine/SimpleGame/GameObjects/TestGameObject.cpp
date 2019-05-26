#include "TestGameObject.h"
#include <Engine/Debug/DebugLog.h>

TestGameObject::TestGameObject(ScrapEngine::Input::InputManager* CreatedInputManager, ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), InputManagerRef(CreatedInputManager), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	set_object_location(glm::vec3(0, 0, 0));
	set_object_rotation(glm::vec3(0, 0, 0));
	set_object_scale(glm::vec3(0.1f, 0.1f, 0.1f));

	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		{ "../assets/textures/Simple_Wood_Crate_Color.png" }
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		{ "../assets/textures/Simple_Wood_Crate_Color.png" }
	));

	(*get_components())[0]->set_component_location(glm::vec3(0, 0, -10));
	(*get_components())[1]->set_component_location(glm::vec3(0, 0, 10));

	ScrapEngine::Debug::DebugLog::print_to_console_log(get_object_location());
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_relative_location());
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[1]->get_component_relative_location());
}

void TestGameObject::game_start()
{
	set_object_location(glm::vec3(0, 10, 0));
	ScrapEngine::Debug::DebugLog::print_to_console_log("---");
	ScrapEngine::Debug::DebugLog::print_to_console_log("Father location");
	ScrapEngine::Debug::DebugLog::print_to_console_log(get_object_location());
	ScrapEngine::Debug::DebugLog::print_to_console_log("Relative location");
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_relative_location());
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[1]->get_component_relative_location());
	ScrapEngine::Debug::DebugLog::print_to_console_log("World location");
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[0]->get_component_location());
	ScrapEngine::Debug::DebugLog::print_to_console_log((*get_components())[1]->get_component_location());
}

void TestGameObject::game_update(float time)
{

}
