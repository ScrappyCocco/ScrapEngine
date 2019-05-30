#pragma once

#include <btBulletDynamicsCommon.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class BroadphaseInterface
		{
		private:
			btBroadphaseInterface* overlapping_pair_cache_ = nullptr;
		public:
			BroadphaseInterface();
			~BroadphaseInterface();

			btBroadphaseInterface* get_broadphase_interface() const;
		};
	}
}
