#pragma once

#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"


class ScoreManager : public ScrapEngine::Core::SGameObject
{
private:
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_view_ref_ = nullptr;
	//Player
	Ball* player_ref_ = nullptr;
	//Window
	ScrapEngine::Render::GameWindow* window_ref_ = nullptr;
	//Vars
	const int max_time_ = 300;
	float current_time_ = 0;

	int score_ = 0;
public:
	ScoreManager(ScrapEngine::Core::LogicManagerView* logic_view,
	         Ball* player,
	         ScrapEngine::Render::GameWindow* window_ref);
	~ScoreManager() = default;

	void increase_score(int amount = 1);
	int get_current_score() const;

	float get_time_elapsed() const;

	void game_update(float time) override;
	void on_gui() override;
};
