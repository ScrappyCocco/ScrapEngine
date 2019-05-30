#include <Engine/Physics/Manager/PhysicsManager.h>
#include <Engine/Physics/CollisionShape/BoxShape/BoxShape.h>
#include <algorithm>

ScrapEngine::Physics::PhysicsManager::PhysicsManager()
{
	b_collision_conf_ = new DefaultCollisionConfiguration();

	c_dispatcher_ = new CollisionDispatcher(b_collision_conf_->get_default_collision_configuration());

	b_interface_ = new BroadphaseInterface();

	impulse_solver_ = new SequentialImpulseConstraintSolver();

	p_world_ = new DiscreteDynamicsWorld(b_collision_conf_->get_default_collision_configuration(),
		c_dispatcher_->get_dispatcher(),
		b_interface_->get_broadphase_interface(),
		impulse_solver_->get_solver());
}

ScrapEngine::Physics::PhysicsManager::~PhysicsManager()
{
	for(RigidBody* body : created_rigid_bodies_)
	{
		delete body;
	}
	delete p_world_;
	delete impulse_solver_;
	delete b_interface_;
	delete c_dispatcher_;
	delete b_collision_conf_;
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
	p_world_->remove_rigidbody(rigidbody->get_rigidbody());
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::PhysicsManager::create_box_collider(
	const Core::SVector3& size,
	const Core::SVector3& start_position, 
	float mass)
{
	BoxShape* box_shape = new BoxShape(size);
	RigidBody* body = new RigidBody();
	body->set_collision_shape(box_shape);
	btTransform initial_position;
	initial_position.setOrigin(btVector3(start_position.get_x(), start_position.get_y(), start_position.get_z()));
	body->set_start_transform(initial_position);
	body->set_mass(mass);
	body->build_rigidbody();

	p_world_->add_rigidbody(body->get_rigidbody());
	created_rigid_bodies_.push_back(body);

	return body;
}
