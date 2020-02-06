#include <Engine/Physics/CollisionShape/BoxShape/BoxShape.h>
#include <Engine/Physics/PhysicsInclude.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

ScrapEngine::Physics::BoxShape::BoxShape(const Core::SVector3& size)
	: CollisionShape(new rp3d::BoxShape(rp3d::Vector3(size.get_x(), size.get_y(), size.get_z())))
{
}
