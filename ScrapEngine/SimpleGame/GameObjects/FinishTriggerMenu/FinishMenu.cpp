#include "FinishMenu.h"
#include "imgui.h"

FinishTriggerMenu::FinishTriggerMenu(ScrapEngine::Core::LogicManagerView* logic_view, Ball* player,
                                     ScrapEngine::Render::GameWindow* window_ref)
	: SGameObject("Main menu Gui manager"),
	  logic_view_ref_(logic_view), player_ref_(player), window_ref_(window_ref)
{
	//Get component
	ScrapEngine::Core::RigidBodyComponent* component = dynamic_cast<ScrapEngine::Core::RigidBodyComponent*>((*
		player_ref_->get_components())[1]);
	if (component)
	{
		test_collision_object_ = component;
	}
	//Create trigger
	box_trigger_ = logic_view->get_components_manager()->create_box_trigger_component(
		ScrapEngine::Core::SVector3(40, 50, 40),
		ScrapEngine::Core::SVector3(425, -20, 75));
}

void FinishTriggerMenu::game_update(float time)
{
	if (box_trigger_->test_collision(test_collision_object_))
	{
		//Set ball in trigger
		in_trigger_ = true;
		set_should_update(false);
		//Disable forces
		test_collision_object_->cancel_rigidbody_forces();
		player_ref_->set_can_move(false);
	}
}

void FinishTriggerMenu::on_gui()
{
	if (in_trigger_)
	{
		ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(0.75f); // Transparent background

		if (ImGui::Begin("Finish Menu UI Overlay", nullptr,
		                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Game Completed!");

			ImGui::Text("Congratulations!");
			const ImVec2 text_box_size = ImGui::GetItemRectSize();

			ImGui::Separator();

			if (ImGui::Button("Exit", ImVec2(text_box_size.x, 20)))
			{
				window_ref_->close_window();
			}

			ImGui::End();
		}
	}
}
