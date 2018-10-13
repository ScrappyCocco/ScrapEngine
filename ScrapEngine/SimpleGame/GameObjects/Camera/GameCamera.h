#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/Rendering/Manager/RenderManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "Engine/Input/KeyboardKeys.h"

class GameCamera : public ScrapEngine::SGameObject
{
private:
	ScrapEngine::Camera* GameCameraRef;
	ScrapEngine::InputManager* InputManagerRef;

	float cameraSpeed = 0.5f;
public:
	GameCamera(ScrapEngine::InputManager* CreatedInputManagerf, ScrapEngine::Camera* input_GameCameraRef);
	~GameCamera() = default;

	virtual void GameStart() override;
	virtual void GameUpdate(float time) override;
};

