#pragma once

#include <btBulletDynamicsCommon.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CollisionShape
		{
		private:
			btCollisionShape* collision_shape_ = nullptr;
		public:
			CollisionShape(btCollisionShape* collision_shape);
			virtual ~CollisionShape() = 0;

			virtual btCollisionShape* get_collision_shape() const;
		};
	}
}
