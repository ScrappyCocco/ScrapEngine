#include <Engine/Physics/CollisionShape/SphereShape/SphereShape.h>


ScrapEngine::Physics::SphereShape::SphereShape(const float radius)
	: CollisionShape(new rp3d::SphereShape(radius))
{
}

