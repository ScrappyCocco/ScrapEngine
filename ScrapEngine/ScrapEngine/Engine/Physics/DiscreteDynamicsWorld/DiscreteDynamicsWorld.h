#pragma once

#include <btBulletDynamicsCommon.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class DiscreteDynamicsWorld
		{
			btDiscreteDynamicsWorld* dynamics_world_ = nullptr;
		public:
			DiscreteDynamicsWorld(btDefaultCollisionConfiguration* collision_configuration,
			                      btCollisionDispatcher* dispatcher,
			                      btBroadphaseInterface* overlapping_pair_cache,
			                      btSequentialImpulseConstraintSolver* solver);
			~DiscreteDynamicsWorld();

			void set_gravity(const Core::SVector3& gravity) const;
			void step_simulation(float delta_time) const;

			void add_collision(btCollisionObject* object) const;
			void remove_collision(btCollisionObject* object) const;

			void add_rigidbody(btRigidBody* body) const;
			void remove_rigidbody(btRigidBody* body) const;
		};
	}
}
