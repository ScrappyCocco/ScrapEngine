#include <Engine/Physics/CollisionShape/CapsuleShape/CapsuleShape.h>
#include <Engine/Physics/PhysicsInclude.h>

ScrapEngine::Physics::CapsuleShape::CapsuleShape(const float radius, const float height)
	: CollisionShape(new rp3d::CapsuleShape(radius, height))
{
}
