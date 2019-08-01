#include "MainMenu.h"
#include "imgui.h"

MainMenu::MainMenu(ScrapEngine::Core::LogicManagerView* logic_view, Ball* player,
                   ScrapEngine::Render::GameWindow* window_ref)
	: SGameObject("Main menu Gui manager"),
	  logic_view_ref_(logic_view), player_ref_(player), window_ref_(window_ref)
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
		                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("ScrapEngine - Example game");
			const ImVec2 text_box_size = ImGui::GetItemRectSize();

			ImGui::Separator();

			if (ImGui::Button("Play", ImVec2(text_box_size.x / 2, 20)))
			{
				game_started_ = true;
				player_ref_->set_can_move(true);
				logic_view_ref_->un_register_game_object(this);
			}
			ImGui::SameLine();
			if (ImGui::Button("Exit", ImVec2(text_box_size.x / 2, 20)))
			{
				window_ref_->close_window();
			}

			ImGui::End();
		}
	}
}
