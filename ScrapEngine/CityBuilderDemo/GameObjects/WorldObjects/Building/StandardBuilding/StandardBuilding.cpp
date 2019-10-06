#include "StandardBuilding.h"

StandardBuilding::StandardBuilding(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
             const ScrapEngine::Core::SVector3& start_pos,
             const ScrapEngine::Core::SVector3& size)
	: BaseBuilding(logic_manager_ref, start_pos, size, color::green)
{
	box_collider_ = component_manager_ref_->create_box_rigidbody_component(
		size * 5,
		start_pos, 0.0f);

	add_component(box_collider_);

	box_collider_->attach_to_mesh(mesh_);
	box_collider_->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	box_collider_->set_friction_coefficient(1);

	//Disable update()
	set_should_update(false);

	//Set mesh scale
	mesh_->set_component_scale(size);
}

void StandardBuilding::die()
{
	//Delete collider
	component_manager_ref_->destroy_rigidbody_component(box_collider_);
	BaseBuilding::die();
}
