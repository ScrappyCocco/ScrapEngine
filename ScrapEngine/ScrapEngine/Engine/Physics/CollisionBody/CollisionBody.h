#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CollisionBody
		{
		private:
			rp3d::Transform transform_;
			CollisionShape* shape_ = nullptr;
			rp3d::ProxyShape* proxy_shape_ = nullptr;

			rp3d::CollisionBody* body_ = nullptr;
		public:
			CollisionBody() = default;
			~CollisionBody();

			void set_start_transform(const rp3d::Vector3& init_position = rp3d::Vector3(0.0, 3.0, 0.0),
			                         const rp3d::Quaternion& init_orientation = rp3d::Quaternion::identity());
			void set_collision_shape(CollisionShape* shape);

			void build_collision_body(rp3d::DynamicsWorld* dynamic_world);
			void remove_from_world(rp3d::DynamicsWorld* dynamic_world) const;

			rp3d::CollisionBody* get_collision_body() const;
			void update_trasform(const Core::STransform& trasform) const;
		};
	}
}
