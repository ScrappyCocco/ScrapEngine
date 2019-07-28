#include "Ball.h"
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/KeyboardKeys.h>
#include <imgui.h>

Ball::Ball(ScrapEngine::Core::ComponentsManager* input_ComponentManager, ScrapEngine::Input::InputManager* CreatedInputManagerf)
	: SGameObject("Ball game object"), ComponentManagerRef(input_ComponentManager), InputManagerRef(CreatedInputManagerf)
{
	//Add mesh to that GameObject
	set_object_scale(ScrapEngine::Core::SVector3(0.5f, 0.5f, 0.5f));

	mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/sphere.obj",
		{ "../assets/textures/SimpleBallTexture.png" }
	);
	add_component(mesh);

	collider = input_ComponentManager->create_sphere_rigidbody_component(
		10.f,
		ScrapEngine::Core::SVector3(0, 20, 0), 5.f);
	add_component(collider);

	collider->attach_to_mesh(mesh);

	collider->set_friction_coefficient(1);
}

void Ball::game_start()
{
}

void Ball::game_update(const float delta_time)
{
	if(InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_UP))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, -700 * (delta_time * 100)));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_DOWN))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(0, 0, 700 * (delta_time * 100)));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_LEFT))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(-700 * (delta_time * 100), 0, 0));
	}
	if (InputManagerRef->get_keyboard_key_pressed(KEYBOARD_KEY_ARROW_RIGHT))
	{
		collider->apply_force_to_center(ScrapEngine::Core::SVector3(700 * (delta_time * 100), 0, 0));
	}
}

void Ball::on_gui()
{
	static int corner = 3;
	const float DISTANCE = 0.0f;
	ImGuiIO& io = ImGui::GetIO();

	if (corner != -1)
	{
		const ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		const ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		//ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

	if (ImGui::Begin("Example: Simple overlay", nullptr, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		auto size = ImGui::GetWindowSize();
		ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", nullptr, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", nullptr, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", nullptr, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
		if (ImGui::Button("Hello button"))
		{
			ScrapEngine::Debug::DebugLog::print_to_console_log("Test");
		}

		ImGui::End();
	}
	
}
