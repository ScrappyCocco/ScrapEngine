#pragma once

#include <Engine/LogicCore/Math/Vector/SVector3.h>
#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class BoxShape : public CollisionShape
		{
		public:
			BoxShape(const Core::SVector3& size);
			~BoxShape() = default;
		};
	}
}
