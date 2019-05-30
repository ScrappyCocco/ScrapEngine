#include <Engine/Physics/DiscreteDynamicsWorld/DiscreteDynamicsWorld.h>

ScrapEngine::Physics::DiscreteDynamicsWorld::DiscreteDynamicsWorld(
	btDefaultCollisionConfiguration* collision_configuration, btCollisionDispatcher* dispatcher,
	btBroadphaseInterface* overlapping_pair_cache, btSequentialImpulseConstraintSolver* solver)
{
	dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher, overlapping_pair_cache, solver, collision_configuration);
	dynamics_world_->setGravity(btVector3(0, -10, 0));
}

ScrapEngine::Physics::DiscreteDynamicsWorld::~DiscreteDynamicsWorld()
{
	delete dynamics_world_;
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::set_gravity(const Core::SVector3& gravity) const
{
	dynamics_world_->setGravity(btVector3(gravity.get_x(), gravity.get_y(), gravity.get_z()));
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::step_simulation(const float delta_time) const
{
	dynamics_world_->stepSimulation(delta_time);
	
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::add_collision(btCollisionObject* object) const
{
	dynamics_world_->addCollisionObject(object);
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::remove_collision(btCollisionObject* object) const
{
	dynamics_world_->removeCollisionObject(object);
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::add_rigidbody(btRigidBody* body) const
{
	dynamics_world_->addRigidBody(body);
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::remove_rigidbody(btRigidBody* body) const
{
	dynamics_world_->removeRigidBody(body);
}
