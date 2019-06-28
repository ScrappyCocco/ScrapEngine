#include <Engine/Physics/Manager/PhysicsManager.h>
#include <Engine/Physics/CollisionShape/BoxShape/BoxShape.h>
#include <algorithm>
#include <Engine/Physics/CollisionShape/SphereShape/SphereShape.h>
#include <Engine/Physics/CollisionShape/CapsuleShape/CapsuleShape.h>

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::PhysicsManager::create_rigidbody(
	const Core::SVector3& start_position, const float mass, CollisionShape* c_shape) const
{
	RigidBody* body = new RigidBody();

	const rp3d::Vector3 start_position_v(start_position.get_x(), start_position.get_y(), start_position.get_z());
	body->set_start_transform(start_position_v);
	body->build_rigidbody(p_world_->get_dynamic_world());
	body->set_mass(mass);
	body->set_collision_shape(c_shape);

	return body;
}

ScrapEngine::Physics::CollisionBody* ScrapEngine::Physics::PhysicsManager::create_collision_body(
	const Core::SVector3& start_position, CollisionShape* c_shape) const
{
	CollisionBody* body = new CollisionBody();

	const rp3d::Vector3 start_position_v(start_position.get_x(), start_position.get_y(), start_position.get_z());
	body->set_start_transform(start_position_v);
	body->build_collision_body(p_world_->get_dynamic_world());
	body->set_collision_shape(c_shape);

	return body;
}

ScrapEngine::Physics::PhysicsManager::PhysicsManager()
{
	p_world_ = new DiscreteDynamicsWorld();
}

ScrapEngine::Physics::PhysicsManager::~PhysicsManager()
{
	//The responsibility to clear the RigidBody* is of the logic manager that create them
	created_rigidbodies_.clear();
	delete p_world_;
}

void ScrapEngine::Physics::PhysicsManager::update_physics(const float delta_time) const
{
	p_world_->step_simulation(delta_time);
}

void ScrapEngine::Physics::PhysicsManager::remove_collider(CollisionBody* collider)
{
	//Remove the collider from the vector
	created_collisionbodies_.erase(std::remove(
		                               created_collisionbodies_.begin(),
		                               created_collisionbodies_.end(),
		                               collider),
	                               created_collisionbodies_.end());
	//Unregister the element
	collider->remove_from_world(p_world_->get_dynamic_world());
}

void ScrapEngine::Physics::PhysicsManager::remove_rigidbody(RigidBody* rigidbody)
{
	//Remove the rigidbody from the vector
	created_rigidbodies_.erase(std::remove(
		                           created_rigidbodies_.begin(),
		                           created_rigidbodies_.end(),
		                           rigidbody),
	                           created_rigidbodies_.end());
	//Unregister the element
	rigidbody->remove_from_world(p_world_->get_dynamic_world());
}

ScrapEngine::Physics::CollisionBody* ScrapEngine::Physics::PhysicsManager::create_box_trigger(
	const Core::SVector3& size,
	const Core::SVector3&
	start_position)
{
	BoxShape* box_shape = new BoxShape(size);
	CollisionBody* body = create_collision_body(start_position, box_shape);

	created_collisionbodies_.push_back(body);

	return body;
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::PhysicsManager::create_box_rigidbody(
	const Core::SVector3& size,
	const Core::SVector3& start_position,
	const float mass)
{
	BoxShape* box_shape = new BoxShape(size);
	RigidBody* body = create_rigidbody(start_position, mass, box_shape);

	created_rigidbodies_.push_back(body);

	return body;
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::PhysicsManager::create_sphere_rigidbody(
	const float radius,
	const Core::SVector3& start_position,
	const float mass)
{
	SphereShape* sphere_shape = new SphereShape(radius);
	RigidBody* body = create_rigidbody(start_position, mass, sphere_shape);

	created_rigidbodies_.push_back(body);

	return body;
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::PhysicsManager::create_capsule_rigidbody(
	const float radius,
	const float height,
	const Core::SVector3& start_position,
	const float mass)
{
	CapsuleShape* capsule_shape = new CapsuleShape(radius, height);
	RigidBody* body = create_rigidbody(start_position, mass, capsule_shape);

	created_rigidbodies_.push_back(body);

	return body;
}
