#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Render::Camera* GameCameraRef;
	ScrapEngine::Input::InputManager* InputManagerRef;
	ScrapEngine::Render::GameWindow* GameWindowRef;

	float camera_speed_ = 0.5f;
	float camera_multiplier_ = 10.f;
public:
	GameCamera(ScrapEngine::Input::InputManager* CreatedInputManagerf, ScrapEngine::Render::Camera* input_GameCameraRef);
	~GameCamera() = default;

	void set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref);

	virtual void game_start() override;
	virtual void game_update(float time) override;
};

