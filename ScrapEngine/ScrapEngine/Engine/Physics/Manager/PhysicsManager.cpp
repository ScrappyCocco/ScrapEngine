#include <Engine/Physics/Manager/PhysicsManager.h>
#include <Engine/Physics/CollisionShape/BoxShape/BoxShape.h>
#include <algorithm>

ScrapEngine::Physics::PhysicsManager::PhysicsManager()
{
	p_world_ = new DiscreteDynamicsWorld();
}

ScrapEngine::Physics::PhysicsManager::~PhysicsManager()
{
	//The responsibility to clear the RigidBody* is of the logic manager that create them
	created_rigid_bodies_.clear();
	delete p_world_;
}

void ScrapEngine::Physics::PhysicsManager::update_physics(const float delta_time) const
{
	p_world_->step_simulation(delta_time);
}

void ScrapEngine::Physics::PhysicsManager::remove_rigidbody(RigidBody* rigidbody)
{
	//Remove the rigidbody from the vector
	created_rigid_bodies_.erase(std::remove(
		                            created_rigid_bodies_.begin(),
		                            created_rigid_bodies_.end(),
		                            rigidbody),
	                            created_rigid_bodies_.end());
	//Unregister the element
	rigidbody->remove_from_world(p_world_->get_dynamic_world());
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::PhysicsManager::create_box_collider(
	const Core::SVector3& size,
	const Core::SVector3& start_position,
	const float mass)
{
	BoxShape* box_shape = new BoxShape(size);
	RigidBody* body = new RigidBody();

	const rp3d::Vector3 start_position_v(start_position.get_x(), start_position.get_y(), start_position.get_z());
	body->set_start_transform(start_position_v);
	body->build_rigidbody(p_world_->get_dynamic_world());
	body->set_mass(mass);
	body->set_collision_shape(box_shape);

	created_rigid_bodies_.push_back(body);

	return body;
}
