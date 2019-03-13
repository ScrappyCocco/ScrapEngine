#include "GameCamera.h"
#include "Engine/Debug/DebugLog.h"
#include "../Camera/GameCamera.h"

GameCamera::GameCamera(ScrapEngine::Input::InputManager* CreatedInputManagerf, ScrapEngine::Camera* input_GameCameraRef, TestGameObject* input_GameObjectRef) :
	GameCameraRef(input_GameCameraRef), SGameObject("Camera-Controller Object"), InputManagerRef(CreatedInputManagerf), GameObjectRef(input_GameObjectRef)
{
	GameCameraRef->setMaxRenderDistance(10000);
}

void GameCamera::GameStart()
{

}

void GameCamera::GameUpdate(float time)
{
	ScrapEngine::Input::mouse_location mouse = InputManagerRef->get_last_mouse_location();
	
	GameCameraRef->ProcessMouseMovement((float)mouse.xpos, (float)mouse.ypos, true);

	cameraSpeed = 10.f * time;
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_W)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() + (cameraSpeed * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_S)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() - (cameraSpeed * GameCameraRef->getCameraFront()));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_D)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() + (cameraSpeed * (glm::normalize(glm::cross(GameCameraRef->getCameraFront(), GameCameraRef->getCameraUp())))));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_A)) {
		GameCameraRef->setCameraLocation(GameCameraRef->getCameraLocation() - (cameraSpeed * (glm::normalize(glm::cross(GameCameraRef->getCameraFront(), GameCameraRef->getCameraUp())))));
	}
	if (InputManagerRef->get_keyboard_key_pressed(MOUSE_BUTTON_LEFT)) {
		GameObjectRef->SpawnCrateAtLocation(GameCameraRef->getCameraLocation());
	}
}

