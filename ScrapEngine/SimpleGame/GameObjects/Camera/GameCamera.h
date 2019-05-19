#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include "../TestGameObject.h"

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Render::Camera* GameCameraRef;
	ScrapEngine::Input::InputManager* InputManagerRef;
	TestGameObject* GameObjectRef;

	float camera_speed_ = 0.5f;
public:
	GameCamera(ScrapEngine::Input::InputManager* CreatedInputManagerf, ScrapEngine::Render::Camera* input_GameCameraRef, TestGameObject* input_GameObjectRef);
	~GameCamera() = default;

	virtual void game_start() override;
	virtual void game_update(float time) override;
};

