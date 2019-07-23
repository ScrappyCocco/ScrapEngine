#include <Engine/Input/Gui/GuiInput.h>
#include <imgui.h>

void ScrapEngine::Input::GuiInput::update_mouse_location(const double x, const double y)
{
	// Update imGui - mouse location
	ImGuiIO& io = ImGui::GetIO();

	if (x > 0 && y > 0 && x < io.DisplaySize.x && y < io.DisplaySize.y) {
		io.MousePos = ImVec2(static_cast<float>(x), static_cast<float>(y));
	}
}

void ScrapEngine::Input::GuiInput::update_mouse_click(const bool left, const bool right)
{
	// Update imGui - mouse click
	ImGuiIO& io = ImGui::GetIO();

	io.MouseDown[0] = left;
	io.MouseDown[1] = right;
}

void ScrapEngine::Input::GuiInput::update_delta_time(const float time)
{
	// Update imGui - delta time
	ImGuiIO& io = ImGui::GetIO();

	io.DeltaTime = time;
}
