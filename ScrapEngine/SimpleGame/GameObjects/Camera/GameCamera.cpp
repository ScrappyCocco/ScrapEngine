#include "GameCamera.h"
#include "Engine/Debug/DebugLog.h"

GameCamera::GameCamera(ScrapEngine::InputManager* CreatedInputManagerf, ScrapEngine::Camera* input_GameCameraRef) : 
	GameCameraRef(input_GameCameraRef), SGameObject("Camera-Controller Object"), InputManagerRef(CreatedInputManagerf)
{
	GameCameraRef->setMaxRenderDistance(500);
}

void GameCamera::GameStart()
{

}

void GameCamera::GameUpdate(float time)
{
	ScrapEngine::MouseLocation mouse = InputManagerRef->getLastMouseLocation();
	
	GameCameraRef->ProcessMouseMovement(mouse.xpos, mouse.ypos, true);

	cameraSpeed = 10.f * time;
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_W) == ScrapEngine::KeyboardKeyState::pressed) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() + (cameraSpeed * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_S) == ScrapEngine::KeyboardKeyState::pressed) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() - (cameraSpeed * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_D) == ScrapEngine::KeyboardKeyState::pressed) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() + (cameraSpeed * (glm::normalize(glm::cross(GameCameraRef->getCameraFront(), GameCameraRef->getCameraUp())))));
	}
	if (InputManagerRef->getKeyboardKeyStatus(keyboard_key_A) == ScrapEngine::KeyboardKeyState::pressed) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() - (cameraSpeed * (glm::normalize(glm::cross(GameCameraRef->getCameraFront(), GameCameraRef->getCameraUp())))));
	}
}

