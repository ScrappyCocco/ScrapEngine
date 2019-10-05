#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Render::Camera* game_camera_ref_ = nullptr;
	ScrapEngine::Input::InputManager* input_manager_ref_ = nullptr;
	ScrapEngine::Render::GameWindow* game_window_ref_ = nullptr;

	float camera_speed_ = 5.5f;
	float camera_multiplier_ = 10.f;
public:
	GameCamera(ScrapEngine::Input::InputManager* created_input_managerf,
	           ScrapEngine::Render::Camera* input_game_camera_ref);
	~GameCamera() = default;

	void set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref);

	void game_start() override;
	void game_update(float time) override;
};
