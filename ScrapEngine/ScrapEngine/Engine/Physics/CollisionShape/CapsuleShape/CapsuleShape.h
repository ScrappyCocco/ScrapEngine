#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CapsuleShape : public CollisionShape
		{
		public:
			CapsuleShape(float radius, float height);
			~CapsuleShape() = default;
		};
	}
}
