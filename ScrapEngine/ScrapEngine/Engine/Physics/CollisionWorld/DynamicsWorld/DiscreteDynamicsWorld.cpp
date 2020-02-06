#include <Engine/Physics/CollisionWorld/DynamicsWorld/DiscreteDynamicsWorld.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

ScrapEngine::Physics::DiscreteDynamicsWorld::DiscreteDynamicsWorld()
{
	world_ = new rp3d::DynamicsWorld(rp3d::Vector3(0.0, -50, 0.0));
}

ScrapEngine::Physics::DiscreteDynamicsWorld::~DiscreteDynamicsWorld()
{
	delete world_;
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::set_gravity(const Core::SVector3& gravity) const
{
	rp3d::Vector3 gravity_vector(gravity.get_x(), gravity.get_y(), gravity.get_z());
	world_->setGravity(gravity_vector);
}

rp3d::Vector3 ScrapEngine::Physics::DiscreteDynamicsWorld::get_gravity() const
{
	return world_->getGravity();
}

void ScrapEngine::Physics::DiscreteDynamicsWorld::step_simulation(const float delta_time) const
{
	world_->update(delta_time);
}

rp3d::DynamicsWorld* ScrapEngine::Physics::DiscreteDynamicsWorld::get_dynamic_world() const
{
	return world_;
}
