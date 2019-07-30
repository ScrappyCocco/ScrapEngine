#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include "../Player/Ball.h"

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Render::Camera* game_camera_ref_ = nullptr;
	ScrapEngine::Input::InputManager* input_manager_ref_ = nullptr;
	ScrapEngine::Render::GameWindow* game_window_ref_ = nullptr;
	Ball* player_ref_ = nullptr;

	float camera_speed_ = 5.5f;
	float camera_multiplier_ = 10.f;
	//Free camera switch
	bool free_camera_ = false;
	bool free_camera_key_pressed_ = false;
public:
	GameCamera(ScrapEngine::Input::InputManager* created_input_managerf, 
		ScrapEngine::Render::Camera* input_game_camera_ref,
		Ball* player);
	~GameCamera() = default;

	void set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref);

	void game_start() override;
	void game_update(float time) override;
};

