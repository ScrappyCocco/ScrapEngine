#pragma once

#include <Engine/Physics/PhysicsInclude.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CollisionShape;

		enum class RigidBody_Types
		{
			static_rigidbody = static_cast<int>(rp3d::BodyType::STATIC),
			kinematic_rigidbody = static_cast<int>(rp3d::BodyType::KINEMATIC),
			dynamic_rigidbody = static_cast<int>(rp3d::BodyType::DYNAMIC)
		};

		class RigidBody
		{
		private:
			rp3d::Transform transform_;
			rp3d::Transform prev_transform_;
			CollisionShape* shape_ = nullptr;
			rp3d::ProxyShape* proxy_shape_ = nullptr;

			rp3d::RigidBody* body_ = nullptr;
		public:
			RigidBody() = default;
			~RigidBody();

			void set_start_transform(const rp3d::Vector3& init_position = rp3d::Vector3(0.0, 3.0, 0.0),
			                         const rp3d::Quaternion& init_orientation = rp3d::Quaternion::identity());
			void set_collision_shape(CollisionShape* shape);

			void set_mass(float mass) const;
			float get_mass() const;

			void set_type(RigidBody_Types type) const;
			RigidBody_Types get_type() const;

			void build_rigidbody(rp3d::DynamicsWorld* dynamic_world);
			void remove_from_world(rp3d::DynamicsWorld* dynamic_world) const;

			//Utils functions for engine
			rp3d::RigidBody* get_rigidbody() const;
			CollisionShape* get_collision_shape() const;

			Core::STransform get_updated_transform(float factor);
			void set_new_transform(const Core::STransform& transform) const;
			void set_new_location(const Core::SVector3& location) const;

			float get_bounciness() const;
			void set_bounciness(float bounce_factor) const;

			float get_friction_coefficient() const;
			void set_friction_coefficient(float coefficient) const;

			bool get_allowed_to_sleep() const;
			void set_allowed_to_sleep(bool allowed) const;

			void apply_force_to_center(const Core::SVector3& force) const;
			void apply_torque(const Core::SVector3& force) const;

			void cancel_rigidbody_forces() const;
		};
	}
}
