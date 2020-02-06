#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace ScrapEngine {
	namespace Core {
		class SVector3;
	}
}

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
