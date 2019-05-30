#pragma once

#include <btBulletDynamicsCommon.h>
#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class RigidBody
		{
		private:
			btTransform start_transform_;
			CollisionShape* shape_ = nullptr;
			float mass_ = 0.f;
			btVector4 color_;
			bool is_dynamic_ = false;

			btRigidBody* body_ = nullptr;
			btDefaultMotionState* motion_state_ = nullptr;
		public:
			RigidBody() = default;
			~RigidBody();

			void set_start_transform(const btTransform& start_transform);
			void set_collision_shape(CollisionShape* shape);
			void set_mass(float mass);
			void set_color(const btVector4& color);
			void build_rigidbody(bool use_motionstate = true);

			btRigidBody* get_rigidbody() const;
		};
	}
}
