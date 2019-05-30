#pragma once

#include <btBulletDynamicsCommon.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class DefaultCollisionConfiguration
		{
		private:
			btDefaultCollisionConfiguration* collision_configuration_ = nullptr;
		public:
			DefaultCollisionConfiguration();
			~DefaultCollisionConfiguration();

			btDefaultCollisionConfiguration* get_default_collision_configuration() const;
		};
	}
}
