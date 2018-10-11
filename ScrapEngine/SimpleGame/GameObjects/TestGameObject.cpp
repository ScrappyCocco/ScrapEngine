#include "TestGameObject.h"
#include "Engine/Debug/DebugLog.h"

TestGameObject::TestGameObject(ScrapEngine::InputManager* CreatedInputManager, ScrapEngine::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), InputManagerRef(CreatedInputManager)
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
	setObjectLocation(glm::vec3(0, 0, -40.0f));
	setObjectRotation(glm::vec3(0, 0, 0));
	setObjectScale(glm::vec3(0.1f, 0.1f, 0.1f));

	AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv",
		"../assets/shader/frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv",
		"../assets/shader/frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv",
		"../assets/shader/frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv",
		"../assets/shader/frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv",
		"../assets/shader/frag.spv",
		"../assets/models/Simple_Wood_Crate.fbx",
		"../assets/textures/Simple_Wood_Crate_Color.png"
	));
	(*GetComponents())[0]->setComponentLocation(glm::vec3(0, 0, -45.0f));
	(*GetComponents())[1]->setComponentLocation(glm::vec3(10, 5, -55.0f));
	(*GetComponents())[2]->setComponentLocation(glm::vec3(20, -7, -70.0f));
	(*GetComponents())[3]->setComponentLocation(glm::vec3(-10, 10, -10.0f));
	(*GetComponents())[4]->setComponentLocation(glm::vec3(-20, -15, -20.0f));
}

void TestGameObject::GameStart()
{
	//ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: START");
}

void TestGameObject::GameUpdate(float time)
{
	
}
