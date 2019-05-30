#pragma once

#include <Engine/Physics/DiscreteDynamicsWorld/DiscreteDynamicsWorld.h>
#include <Engine/Physics/RigidBody/RigidBody.h>
#include <vector>

namespace ScrapEngine
{
	namespace Physics
	{
		class PhysicsManager
		{
		private:
			DiscreteDynamicsWorld* p_world_ = nullptr;

			std::vector<RigidBody*> created_rigid_bodies_;
		public:
			PhysicsManager();
			~PhysicsManager();

			void update_physics(float delta_time) const;
			void remove_rigidbody(RigidBody* rigidbody);

			RigidBody* create_box_collider(const Core::SVector3& size,
			                               const Core::SVector3& start_position,
			                               float mass = 0.f);
		};
	}
}
