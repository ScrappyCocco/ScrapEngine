#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include "../Player/Ball.h"

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Render::Camera* game_camera_ref_;
	ScrapEngine::Input::InputManager* input_manager_ref_;
	ScrapEngine::Render::GameWindow* game_window_ref_;
	Ball* player_ref_;

	float camera_speed_ = 0.5f;
	float camera_multiplier_ = 10.f;
public:
	GameCamera(ScrapEngine::Input::InputManager* created_input_managerf, 
		ScrapEngine::Render::Camera* input_game_camera_ref,
		Ball* player);
	~GameCamera() = default;

	void set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref);

	virtual void game_start() override;
	virtual void game_update(float time) override;
};

