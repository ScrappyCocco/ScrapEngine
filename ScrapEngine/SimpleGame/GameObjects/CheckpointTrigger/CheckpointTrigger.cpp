#include "CheckpointTrigger.h"
#include "imgui.h"

CheckpointTrigger::CheckpointTrigger(ScrapEngine::Core::LogicManagerView* logic_view,
                                     Ball* player,
                                     const ScrapEngine::Core::SVector3& pos)
	: SGameObject("Main menu Gui manager"), player_ref_(player)
{
	set_object_location(pos);
	pos_ = pos;

	//Get component
	ScrapEngine::Core::RigidBodyComponent* component = dynamic_cast<ScrapEngine::Core::RigidBodyComponent*>((*
		player_ref_->get_components())[1]);
	if (component)
	{
		test_collision_object_ = component;
	}
	//Create trigger
	box_trigger_ = logic_view->get_components_manager()->create_box_trigger_component(
		ScrapEngine::Core::SVector3(3, 3, 3) * 5,
		pos);

	//Create Mesh
	ScrapEngine::Core::MeshComponent* mesh = logic_view->get_components_manager()->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/SimpleCheckpoint.obj",
		{
			"../assets/textures/SimpleDarkGreyTexture.png",
			//First arrow
			"../assets/textures/SimpleGreyTexture.png",
			//First cylinder
			"../assets/textures/SimpleDarkGreyTexture.png",
			//Center
			"../assets/textures/SimpleDarkGreyTexture.png",
			//Second cylinder
			"../assets/textures/SimpleGreyTexture.png",
			//Third cylinder
			"../assets/textures/SimpleDarkGreyTexture.png",
			//Arrows
			"../assets/textures/SimpleDarkGreyTexture.png",
			"../assets/textures/SimpleDarkGreyTexture.png",
		}
	);
	add_component(mesh);
	mesh->set_component_scale(ScrapEngine::Core::SVector3(3, 3, 3));
	mesh->set_is_static(true);

	//Main center Collider
	ScrapEngine::Core::RigidBodyComponent* box_collider = logic_view
	                                                      ->get_components_manager()->create_box_rigidbody_component(
		                                                      ScrapEngine::Core::SVector3(5, 0.5, 5) * 5,
		                                                      pos - ScrapEngine::Core::SVector3(0, 1.5, 0), 0.f);
	box_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	box_collider->set_bounciness(0);
	box_collider->set_friction_coefficient(1);

	//Arrow angles Collider

	const ScrapEngine::Core::SVector3 arrow_collider_size = ScrapEngine::Core::SVector3(0.5, 0.05f, 0.5) * 5;

	const ScrapEngine::Core::SVector3 right_angle = pos + ScrapEngine::Core::SVector3(25, 1, 0);
	ScrapEngine::Core::RigidBodyComponent* right_angle_collider = logic_view
	                                                              ->get_components_manager()->
	                                                              create_box_rigidbody_component(
		                                                              arrow_collider_size,
		                                                              right_angle, 0.f);
	right_angle_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	right_angle_collider->set_bounciness(0);
	right_angle_collider->set_friction_coefficient(1);

	const ScrapEngine::Core::SVector3 left_angle = pos + ScrapEngine::Core::SVector3(-25, 1, 0);
	ScrapEngine::Core::RigidBodyComponent* left_angle_collider = logic_view
	                                                             ->get_components_manager()->
	                                                             create_box_rigidbody_component(
		                                                             arrow_collider_size,
		                                                             left_angle, 0.f);
	left_angle_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	left_angle_collider->set_bounciness(0);
	left_angle_collider->set_friction_coefficient(1);

	const ScrapEngine::Core::SVector3 up_angle = pos + ScrapEngine::Core::SVector3(0, 1, -25);
	ScrapEngine::Core::RigidBodyComponent* up_angle_collider = logic_view
	                                                           ->get_components_manager()->
	                                                           create_box_rigidbody_component(
		                                                           arrow_collider_size,
		                                                           up_angle, 0.f);
	up_angle_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	up_angle_collider->set_bounciness(0);
	up_angle_collider->set_friction_coefficient(1);

	const ScrapEngine::Core::SVector3 bottom_angle = pos + ScrapEngine::Core::SVector3(0, 1, 25);
	ScrapEngine::Core::RigidBodyComponent* bottom_angle_collider = logic_view
	                                                               ->get_components_manager()->
	                                                               create_box_rigidbody_component(
		                                                               arrow_collider_size,
		                                                               bottom_angle, 0.f);
	bottom_angle_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	bottom_angle_collider->set_bounciness(0);
	bottom_angle_collider->set_friction_coefficient(1);
}

void CheckpointTrigger::game_update(const float time)
{
	if (in_trigger_)
	{
		//Display gui timer
		timer_ += time;
		if (timer_ >= 2)
		{
			set_should_update(false);
		}
	}
	else
	{
		//Trigger check
		if (box_trigger_->test_collision(test_collision_object_))
		{
			//Set ball in trigger
			in_trigger_ = true;
			//Set spawnpoint
			player_ref_->set_spawnpoint(pos_ + ScrapEngine::Core::SVector3(0, 15, 0));
		}
	}
}

void CheckpointTrigger::on_gui()
{
	if (in_trigger_ && timer_ < 2)
	{
		ImGui::SetNextWindowBgAlpha(0.75f); // Transparent background

		//Set pos in the corner
		const float distance = 10.0f;
		const ImVec2 window_pos = ImVec2(distance, distance + 60);
		const ImVec2 window_pos_pivot = ImVec2(0, 0);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

		if (ImGui::Begin("Checkpoint notification UI Overlay", nullptr,
		                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration |
		                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
		                 ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Checkpoint activated!");

			ImGui::End();
		}
	}
}
