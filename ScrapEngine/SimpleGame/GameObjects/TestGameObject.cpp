#include "TestGameObject.h"

TestGameObject::TestGameObject(ScrapEngine::Input::InputManager* CreatedInputManager, ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), InputManagerRef(CreatedInputManager), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	/*AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv", 
		"../assets/shader/frag.spv", 
		"../assets/models/chess/ChessPieces/King.fbx", 
		"../assets/textures/SimpleGreenTexture.png"
	));
	setObjectLocation(glm::vec3(0, 0, -20.0f));
	setObjectRotation(glm::vec3(0, 0, 0));
	setObjectScale(glm::vec3(0.5f, 0.5f, 0.5f));*/
	set_object_location(glm::vec3(0, 0, -40.0f));
	set_object_rotation(glm::vec3(0, 0, 0));
	set_object_scale(glm::vec3(0.1f, 0.1f, 0.1f));

	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/shader_base.vert.spv",
		"../assets/shader/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/shader_base.vert.spv",
		"../assets/shader/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/shader_base.vert.spv",
		"../assets/shader/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/shader_base.vert.spv",
		"../assets/shader/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	add_component(input_ComponentManager->create_new_mesh_component(
		"../assets/shader/shader_base.vert.spv",
		"../assets/shader/shader_base.frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	(*get_components())[0]->set_component_location(glm::vec3(0, 0, -45.0f));
	(*get_components())[1]->set_component_location(glm::vec3(10, 5, -55.0f));
	(*get_components())[2]->set_component_location(glm::vec3(20, -7, -70.0f));
	(*get_components())[3]->set_component_location(glm::vec3(-10, 10, -10.0f));
	(*get_components())[4]->set_component_location(glm::vec3(-20, -15, -20.0f));
}

void TestGameObject::game_start()
{
}

void TestGameObject::game_update(float time)
{
	
}
