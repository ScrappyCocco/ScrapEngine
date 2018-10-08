#include "TestGameObject.h"
#include "Engine/Debug/DebugLog.h"

TestGameObject::TestGameObject(ScrapEngine::InputManager* CreatedInputManager) : SGameObject("Test game object"), InputManagerRef(CreatedInputManager)
{

}

TestGameObject::~TestGameObject()
{

}

void TestGameObject::GameStart()
{
	//ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: START");
}

void TestGameObject::GameUpdate()
{
	//ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: UPDATE");
	if (InputManagerRef->getKeyboardKeyStatus(ScrapEngine::KeyboardKeysList::keyboard_key_w) == ScrapEngine::KeyboardKeyState::pressed) {
		ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: Key Pressed");
	}
	else {
		ScrapEngine::DebugLog::printToConsoleLog("GAMEOBJECT: Key Released");
	}
	ScrapEngine::MouseLocation location = InputManagerRef->getLastMouseLocation();
	ScrapEngine::DebugLog::printToConsoleLog("Location:" + std::to_string(location.xpos) + " - " + std::to_string(location.ypos));
}
