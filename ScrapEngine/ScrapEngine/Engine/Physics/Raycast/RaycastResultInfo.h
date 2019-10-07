#pragma once

#include <Engine/LogicCore/Math/Vector/SVector3.h>
#include <Engine/Physics/RigidBody/RigidBody.h>

namespace ScrapEngine
{
	namespace Physics
	{
		/**
		 * \brief This class is used by the engine to return a raycast result
		 */
		class RaycastResultInfo
		{
		public:
			/**
			 * \brief Hit point in world-space coordinates 
			 */
			Core::SVector3 world_point;
			/**
			 * \brief Surface normal of the proxy shape at the hit point in world-space coordinates 
			 */
			Core::SVector3 world_normal;
			/**
			 * \brief Fraction distance of the hit point between startPoint and endPoint of the ray.
			 * The hit point p is such that p = startPoint + hitFraction ⋅ (endPoint - startPoint)
			 */
			float hit_fraction;
			/**
			 * \brief Pointer to the collision body or rigid body that has been hit by the ray
			 * (or nullptr if empty)
			 */
			RigidBody* body = nullptr;
			/**
			 * \brief Pointer to the proxy shape that has been hit by the ray
			 * (or nullptr if empty)
			 */
			CollisionShape* proxy_shape = nullptr;

			RaycastResultInfo() = default;
			RaycastResultInfo(
				const Core::SVector3& p_world_point,
				const Core::SVector3& p_world_normal,
				float p_hit_fraction,
				RigidBody* p_body,
				CollisionShape* p_proxy_shape
			);

			RaycastResultInfo& operator=(const RaycastResultInfo& other) = default;
			RaycastResultInfo& operator=(RaycastResultInfo&& other) = default;
			RaycastResultInfo(const RaycastResultInfo& other) = default;
			RaycastResultInfo(RaycastResultInfo&& other) = default;

			~RaycastResultInfo() = default;
		};
	}
}
