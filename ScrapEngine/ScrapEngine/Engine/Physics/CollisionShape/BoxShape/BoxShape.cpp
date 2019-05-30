#include <Engine/Physics/CollisionShape/BoxShape/BoxShape.h>


ScrapEngine::Physics::BoxShape::BoxShape(const Core::SVector3& size)
	: CollisionShape(new btBoxShape(btVector3(size.get_x(), size.get_y(), size.get_z())))
{
}

