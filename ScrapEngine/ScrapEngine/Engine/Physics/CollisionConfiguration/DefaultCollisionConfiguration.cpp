#include <Engine/Physics/CollisionConfiguration/DefaultCollisionConfiguration.h>


ScrapEngine::Physics::DefaultCollisionConfiguration::DefaultCollisionConfiguration()
{
	collision_configuration_ = new btDefaultCollisionConfiguration();
}

ScrapEngine::Physics::DefaultCollisionConfiguration::~DefaultCollisionConfiguration()
{
	delete collision_configuration_;
}

btDefaultCollisionConfiguration* ScrapEngine::Physics::DefaultCollisionConfiguration::
get_default_collision_configuration() const
{
	return collision_configuration_;
}
