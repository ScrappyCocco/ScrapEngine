#include <Engine/Physics/CollisionShape/CollisionShape.h>

ScrapEngine::Physics::CollisionShape::CollisionShape(reactphysics3d::CollisionShape* collision_shape)
	: collision_shape_(collision_shape)
{
}

ScrapEngine::Physics::CollisionShape::~CollisionShape()
{
	delete collision_shape_;
}

reactphysics3d::CollisionShape* ScrapEngine::Physics::CollisionShape::get_collision_shape() const
{
	return collision_shape_;
}
