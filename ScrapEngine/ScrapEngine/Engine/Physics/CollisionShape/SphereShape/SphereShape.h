#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class SphereShape : public CollisionShape
		{
		public:
			SphereShape(float radius);
			~SphereShape() = default;
		};
	}
}
