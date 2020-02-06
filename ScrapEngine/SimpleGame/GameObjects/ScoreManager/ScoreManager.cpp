#include "ScoreManager.h"
#include "imgui.h"
#include <Engine/Rendering/Window/GameWindow.h>

ScoreManager::ScoreManager(Ball* player, ScrapEngine::Render::GameWindow* window_ref)
	: SGameObject("Score & relative Gui manager"),
	  player_ref_(player), window_ref_(window_ref)
{
	current_time_ = static_cast<float>(max_time_);
}

void ScoreManager::increase_score(const int amount)
{
	score_ += amount;
}

int ScoreManager::get_current_score() const
{
	return score_;
}

float ScoreManager::get_time_elapsed() const
{
	return max_time_ - current_time_;
}

void ScoreManager::game_update(const float time)
{
	if (player_ref_->get_can_move())
	{
		current_time_ -= time;
	}
	if (current_time_ <= 0)
	{
		player_ref_->set_can_move(false);
	}
}

void ScoreManager::on_gui()
{
	if (player_ref_->get_can_move() || current_time_ <= 0)
	{
		if (current_time_ > 0)
		{
			ImGui::SetNextWindowBgAlpha(0.75f); // Transparent background

			//Set pos in the corner
			const float distance = 10.0f;
			const ImVec2 window_pos = ImVec2(distance, distance);
			const ImVec2 window_pos_pivot = ImVec2(0.0f, 0.0f);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

			if (ImGui::Begin("Score Menu UI Overlay", nullptr,
			                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration |
			                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
			                 ImGuiWindowFlags_NoNav))
			{
				ImGui::Text("Time remaining: %.1fs", current_time_);

				ImGui::Separator();

				ImGui::Text("Score: %i", score_);

				ImGui::End();
			}
		}
		else //No more time
		{
			ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
			ImGui::SetNextWindowBgAlpha(0.75f); // Transparent background

			if (ImGui::Begin("Lose Menu UI Overlay", nullptr,
			                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize
			                 | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav))
			{
				ImGui::Text("You lose!");

				ImGui::Text("No more time left!");
				const ImVec2 text_box_size = ImGui::GetItemRectSize();

				ImGui::Text("Final score: %i", score_);

				ImGui::Separator();

				if (ImGui::Button("Exit", ImVec2(text_box_size.x, 20)))
				{
					window_ref_->close_window();
				}

				ImGui::End();
			}
		}
	}
}
