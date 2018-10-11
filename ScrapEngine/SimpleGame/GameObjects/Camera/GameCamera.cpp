#include "GameCamera.h"
#include "Engine/Debug/DebugLog.h"

GameCamera::GameCamera(ScrapEngine::InputManager* CreatedInputManagerf, ScrapEngine::Camera* input_GameCameraRef) : 
	GameCameraRef(input_GameCameraRef), SGameObject("Camera-Controller Object"), InputManagerRef(CreatedInputManagerf)
{

}

void GameCamera::GameStart()
{
	GameCameraRef->setCameraLocation(glm::vec3(0, 0, -60));
}

void GameCamera::GameUpdate(float time)
{
	ScrapEngine::MouseLocation mouse = InputManagerRef->getLastMouseLocation();
	ScrapEngine::DebugLog::printToConsoleLog("Mouse x:" + std::to_string(mouse.xpos) + " y:" + std::to_string(mouse.ypos));
	if (firstMouseRead) {
		firstMouseRead = false;
		lastX = mouse.xpos;
		lastY = mouse.ypos;
	}
	float xoffset = mouse.xpos - lastX;
	float yoffset = lastY - mouse.ypos; // reversed since y-coordinates range from bottom to top
	lastX = mouse.xpos;
	lastY = mouse.ypos;
	
	GameCameraRef->ProcessMouseMovement(xoffset, yoffset, false);

	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_W) == ScrapEngine::KeyboardKeyState::pressed) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraTransform().location + (2.5f * time * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_S) == ScrapEngine::KeyboardKeyState::pressed) {
		//GameCameraRef->setCameraLocation();
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_D) == ScrapEngine::KeyboardKeyState::pressed) {
		
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_A) == ScrapEngine::KeyboardKeyState::pressed) {
		
	}
	//ScrapEngine::DebugLog::printToConsoleLog(GameCameraRef->getCameraTransform().toString());
}

