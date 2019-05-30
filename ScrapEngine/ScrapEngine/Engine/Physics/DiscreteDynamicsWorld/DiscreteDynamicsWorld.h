#pragma once

#include <reactphysics3d.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

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
			void step_simulation(float delta_time) const;

			rp3d::DynamicsWorld* get_dynamic_world() const;
		};
	}
}
