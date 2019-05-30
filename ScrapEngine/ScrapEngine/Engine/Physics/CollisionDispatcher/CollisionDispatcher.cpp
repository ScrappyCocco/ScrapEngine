#include <Engine/Physics/CollisionDispatcher/CollisionDispatcher.h>

ScrapEngine::Physics::CollisionDispatcher::CollisionDispatcher(btDefaultCollisionConfiguration* collision_configuration)
{
	dispatcher_ = new btCollisionDispatcher(collision_configuration);
}

ScrapEngine::Physics::CollisionDispatcher::~CollisionDispatcher()
{
	delete dispatcher_;
}

btCollisionDispatcher* ScrapEngine::Physics::CollisionDispatcher::get_dispatcher() const
{
	return dispatcher_;
}
