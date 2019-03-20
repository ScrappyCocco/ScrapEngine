#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/Rendering/Manager/RenderManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "Engine/Input/KeyboardKeys.h"
#include "Engine/Input/MouseButtons.h"
#include "../TestGameObject.h"

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Camera* GameCameraRef;
	ScrapEngine::Input::InputManager* InputManagerRef;
	TestGameObject* GameObjectRef;

	float cameraSpeed = 0.5f;
public:
	GameCamera(ScrapEngine::Input::InputManager* CreatedInputManagerf, ScrapEngine::Camera* input_GameCameraRef, TestGameObject* input_GameObjectRef);
	~GameCamera() = default;

	virtual void game_start() override;
	virtual void game_update(float time) override;
};

