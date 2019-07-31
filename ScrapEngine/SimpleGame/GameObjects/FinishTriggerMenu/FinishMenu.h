#pragma once

#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"


class FinishTriggerMenu : public ScrapEngine::Core::SGameObject
{
private:
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_view_ref_ = nullptr;
	//Player
	Ball* player_ref_ = nullptr;
	//Window
	ScrapEngine::Render::GameWindow* window_ref_ = nullptr;
	//Trigger
	ScrapEngine::Core::TriggerComponent* box_trigger_;
	//Object to test collision
	ScrapEngine::Core::RigidBodyComponent* test_collision_object_;

	bool in_trigger_ = false;
public:
	FinishTriggerMenu(ScrapEngine::Core::LogicManagerView* logic_view,
	         Ball* player,
	         ScrapEngine::Render::GameWindow* window_ref);
	~FinishTriggerMenu() = default;

	void game_update(float time) override;
	void on_gui() override;
};
