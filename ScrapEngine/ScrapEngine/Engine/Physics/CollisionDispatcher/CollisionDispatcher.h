#pragma once

#include <btBulletDynamicsCommon.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CollisionDispatcher
		{
		private:
			btCollisionDispatcher* dispatcher_ = nullptr;
		public:
			CollisionDispatcher(btDefaultCollisionConfiguration* collision_configuration);
			~CollisionDispatcher();

			btCollisionDispatcher* get_dispatcher() const;
		};
	}
}

