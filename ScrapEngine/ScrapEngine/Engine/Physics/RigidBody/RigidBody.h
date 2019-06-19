#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Physics
	{
		enum RigidBody_Types
		{
			static_rigidbody = rp3d::BodyType::STATIC,
			kinematic_rigidbody = rp3d::BodyType::KINEMATIC,
			dynamic_rigidbody = rp3d::BodyType::DYNAMIC
		};

		class RigidBody
		{
		private:
			rp3d::Transform transform_;
			rp3d::Transform prev_transform_;
			CollisionShape* shape_ = nullptr;
			rp3d::ProxyShape* proxy_shape_ = nullptr;

			rp3d::RigidBody* body_ = nullptr;

			static Core::STransform convert_transform(const rp3d::Transform& other);
			static rp3d::Transform convert_transform(const Core::STransform& other);
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

			rp3d::RigidBody* get_rigidbody() const;
			Core::STransform get_updated_transform(float factor);
			void set_new_transform(const Core::STransform& transform) const;
		};
	}
}
