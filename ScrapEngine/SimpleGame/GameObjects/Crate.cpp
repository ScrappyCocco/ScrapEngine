#include "Crate.h"
#include <Engine/Debug/DebugLog.h>

Crate::Crate(ScrapEngine::Core::LogicManagerView* logic_manager_ref, const ScrapEngine::Core::SVector3& start_pos)
	: SGameObject("Crate game object"), logic_manager_view_(logic_manager_ref),
	component_manager_ref_(logic_manager_ref->get_components_manager())
{
	//Add mesh to that GameObject
	mesh_ = component_manager_ref_->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/Simple_Wood_Crate_Color.png" }
	);
	add_component(mesh_);

	box_collider_ = component_manager_ref_->create_box_rigidbody_component(
		ScrapEngine::Core::SVector3(8.f, 8.f, 8.f),
		start_pos, 1.f);
	
	add_component(box_collider_);

	box_collider_->attach_to_mesh(mesh_);
	box_collider_->set_bounciness(0.f);
	box_collider_->set_friction_coefficient(1);

	//Disable update()
	set_should_update(false);

	//Set mesh scale
	mesh_->set_component_scale(ScrapEngine::Core::SVector3(1.5f, 1.5f, 1.5f));
}

void Crate::die()
{
	mesh_->set_is_visible(false);
	//Delete trigger
	component_manager_ref_->destroy_rigidbody_component(box_collider_);
	//Delete mesh
	component_manager_ref_->destroy_mesh_component(mesh_);
	//Delete this
	logic_manager_view_->un_register_game_object(this);
}
