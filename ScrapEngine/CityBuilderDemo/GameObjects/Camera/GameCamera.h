#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include "../RaycastManager/RaycastManager.h"

class GameCamera : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Render::Camera* game_camera_ref_ = nullptr;
	ScrapEngine::Input::InputManager* input_manager_ref_ = nullptr;
	ScrapEngine::Render::GameWindow* game_window_ref_ = nullptr;
	RaycastManager* raycast_manager_;

	float camera_speed_ = 5.5f;
	float camera_multiplier_ = 10.f;

	bool click_only_ = true;
public:
	GameCamera(ScrapEngine::Input::InputManager* created_input_manager,
	           ScrapEngine::Render::Camera* input_game_camera_ref);
	~GameCamera() = default;

	void set_game_window_ref(ScrapEngine::Render::GameWindow* window_ref);
	void set_raycast_manager(RaycastManager* raycast_manager_ref);

	void game_start() override;
	void game_update(float time) override;
};
