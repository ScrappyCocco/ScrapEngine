#include "GameCamera.h"
#include "Engine/Debug/DebugLog.h"
#include "../Camera/GameCamera.h"

GameCamera::GameCamera(ScrapEngine::InputManager* CreatedInputManagerf, ScrapEngine::Camera* input_GameCameraRef, TestGameObject* input_GameObjectRef) :
	GameCameraRef(input_GameCameraRef), SGameObject("Camera-Controller Object"), InputManagerRef(CreatedInputManagerf), GameObjectRef(input_GameObjectRef)
{
	GameCameraRef->setMaxRenderDistance(10000);
}

void GameCamera::GameStart()
{

}

void GameCamera::GameUpdate(const float& time)
{
	ScrapEngine::MouseLocation mouse = InputManagerRef->getLastMouseLocation();
	
	GameCameraRef->ProcessMouseMovement((float)mouse.xpos, (float)mouse.ypos, true);

	cameraSpeed = 10.f * time;
	if (InputManagerRef->getKeyboardKeyPressed(keyboard_key_W)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() + (cameraSpeed * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->getKeyboardKeyPressed(keyboard_key_S)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() - (cameraSpeed * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->getKeyboardKeyPressed(keyboard_key_D)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() + (cameraSpeed * (glm::normalize(glm::cross(GameCameraRef->getCameraFront(), GameCameraRef->getCameraUp())))));
	}
	if (InputManagerRef->getKeyboardKeyPressed(keyboard_key_A)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() - (cameraSpeed * (glm::normalize(glm::cross(GameCameraRef->getCameraFront(), GameCameraRef->getCameraUp())))));
	}
	if (InputManagerRef->getMouseButtonPressed(mouse_button_left)) {
		GameObjectRef->SpawnCrateAtLocation(GameCameraRef->getCameraLocation());
	}
}

