#pragma once

#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"


class MainMenu : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::LogicManagerView* logic_view_ref_ = nullptr;
	Ball* player_ref_ = nullptr;
	ScrapEngine::Render::GameWindow* window_ref_ = nullptr;
	ScrapEngine::Input::InputManager* input_ref_ = nullptr;

	bool game_started_ = false;
	bool play_button_cursor_changed_ = false;
	bool exit_button_cursor_changed_ = false;
public:
	MainMenu(ScrapEngine::Core::LogicManagerView* logic_view,
	         Ball* player,
	         ScrapEngine::Render::GameWindow* window_ref,
	         ScrapEngine::Input::InputManager* input_ref);
	~MainMenu() = default;
private:
	void on_gui() override;

	void set_hand_cursor() const;
	void set_arrow_cursor() const;
};
