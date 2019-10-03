#include "MainMenu.h"
#include "imgui.h"

MainMenu::MainMenu(ScrapEngine::Core::LogicManagerView* logic_view, Ball* player,
                   ScrapEngine::Render::GameWindow* window_ref,
                   ScrapEngine::Input::InputManager* input_ref)
	: SGameObject("Main menu Gui manager"),
	  logic_view_ref_(logic_view), player_ref_(player), window_ref_(window_ref), input_ref_(input_ref)
{
	player_ref_->set_can_move(false);
}

void MainMenu::on_gui()
{
	if (!game_started_)
	{
		ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(0.55f); // Transparent background

		if (ImGui::Begin("Main Menu UI Overlay", nullptr,
		                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("ScrapEngine - Example game");
			const ImVec2 text_box_size = ImGui::GetItemRectSize();

			ImGui::Separator();
			//-----------------------------------
			//Play button
			if (ImGui::Button("Play", ImVec2(text_box_size.x / 2, 20)))
			{
				game_started_ = true;

				//Reset cursor
				if (play_button_cursor_changed_)
				{
					play_button_cursor_changed_ = false;
					set_arrow_cursor();
				}

				//Grab cursor
				player_ref_->set_can_move(true);
				//Destroy main menu
				logic_view_ref_->un_register_game_object(this);
			}
			//Play button Hover
			if (!game_started_)
			{
				if (ImGui::IsItemHovered())
				{
					if (!play_button_cursor_changed_)
					{
						play_button_cursor_changed_ = true;
						set_hand_cursor();
					}
				}
				else if (play_button_cursor_changed_)
				{
					play_button_cursor_changed_ = false;
					set_arrow_cursor();
				}
			}
			//-----------------------------------
			ImGui::SameLine();
			//-----------------------------------
			//Exit button
			if (ImGui::Button("Exit", ImVec2(text_box_size.x / 2, 20)))
			{
				window_ref_->close_window();
			}
			//Exit button Hover
			if (!game_started_)
			{
				if (ImGui::IsItemHovered())
				{
					if (!exit_button_cursor_changed_)
					{
						exit_button_cursor_changed_ = true;
						set_hand_cursor();
					}
				}
				else if (exit_button_cursor_changed_)
				{
					exit_button_cursor_changed_ = false;
					set_arrow_cursor();
				}
			}
			//-----------------------------------
			ImGui::End();
		}
	}
}

void MainMenu::set_hand_cursor() const
{
	input_ref_->load_system_cursor(ScrapEngine::Input::system_cursor_shapes::cursor_hand_shape);
}

void MainMenu::set_arrow_cursor() const
{
	input_ref_->load_system_cursor(ScrapEngine::Input::system_cursor_shapes::cursor_regular_arrow);
}
