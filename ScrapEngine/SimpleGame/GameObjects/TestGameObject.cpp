#include "TestGameObject.h"
#include "Engine/Debug/DebugLog.h"

TestGameObject::TestGameObject(ScrapEngine::InputManager* CreatedInputManager, ScrapEngine::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), InputManagerRef(CreatedInputManager)
{
	//Add mesh to that GameObject
	AddComponent(input_ComponentManager->createNewMeshComponent(
		"../assets/shader/vert.spv", 
		"../assets/shader/frag.spv", 
		"../assets/models/chess/ChessPieces/Queen.fbx", 
		"../assets/textures/SimpleGreenTexture.png"
	));
	setObjectLocation(glm::vec3(0, 0, -10.0f));
	setObjectRotation(glm::vec3(0, 0, 0));
	setObjectScale(glm::vec3(0.5f, 0.5f, 0.5f));
}

void TestGameObject::GameStart()
{
	//ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: START");
}

void TestGameObject::GameUpdate()
{
	//ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: UPDATE");
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_W) == ScrapEngine::KeyboardKeyState::pressed){
		setObjectLocation(getObjectLocation() + glm::vec3(0, 0, 0.001f));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_S) == ScrapEngine::KeyboardKeyState::pressed) {
		setObjectLocation(getObjectLocation() + glm::vec3(0, 0, -0.001f));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_E) == ScrapEngine::KeyboardKeyState::pressed) {
		setObjectLocation(getObjectLocation() + glm::vec3(0, 0.001f, 0));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_Q) == ScrapEngine::KeyboardKeyState::pressed) {
		setObjectLocation(getObjectLocation() + glm::vec3(0, -0.001f, 0));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_D) == ScrapEngine::KeyboardKeyState::pressed) {
		setObjectLocation(getObjectLocation() + glm::vec3(0.001f, 0, 0));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_A) == ScrapEngine::KeyboardKeyState::pressed) {
		setObjectLocation(getObjectLocation() + glm::vec3(-0.001f, 0, 0));
	}
}
