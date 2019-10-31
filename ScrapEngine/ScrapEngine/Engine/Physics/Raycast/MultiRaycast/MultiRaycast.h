#pragma once

#include <Engine/LogicCore/Math/Vector/SVector3.h>
#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/Physics/Raycast/RaycastResultInfo.h>
#include <vector>

namespace ScrapEngine
{
	namespace Physics
	{
		class MultiRaycast : public rp3d::RaycastCallback
		{
		private:
			rp3d::DynamicsWorld* world_ref_ = nullptr;

			std::vector<RaycastResultInfo> last_raycast_result_;
			const std::vector<RigidBody*>* created_rigidbodies_ref_ = nullptr;

			RigidBody* search_rigidbody(const rp3d::CollisionBody* body) const;

			reactphysics3d::decimal notifyRaycastHit(const reactphysics3d::RaycastInfo& info) override;
		public:
			MultiRaycast(rp3d::DynamicsWorld* world_ref);
			~MultiRaycast() = default;

			std::vector<RaycastResultInfo> execute_ray(const Core::SVector3& start,
			                                           const Core::SVector3& end,
			                                           const std::vector<RigidBody*>* created_rigidbodies);
		};
	}
}