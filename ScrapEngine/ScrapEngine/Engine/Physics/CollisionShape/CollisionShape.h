#pragma once

#include <reactphysics3d.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CollisionShape
		{
		private:
			reactphysics3d::CollisionShape* collision_shape_ = nullptr;
		public:
			CollisionShape(reactphysics3d::CollisionShape* collision_shape);
			virtual ~CollisionShape() = 0;

			virtual reactphysics3d::CollisionShape* get_collision_shape() const;
		};
	}
}
