#pragma once

#include <Engine/Physics/PhysicsInclude.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SVector3;
	}
}

namespace ScrapEngine
{
	namespace Physics
	{
		class DiscreteDynamicsWorld
		{
			rp3d::DynamicsWorld* world_ = nullptr;
		public:
			DiscreteDynamicsWorld();
			~DiscreteDynamicsWorld();

			void set_gravity(const Core::SVector3& gravity) const;
			rp3d::Vector3 get_gravity() const;

			void step_simulation(float delta_time) const;

			rp3d::DynamicsWorld* get_dynamic_world() const;
		};
	}
}
