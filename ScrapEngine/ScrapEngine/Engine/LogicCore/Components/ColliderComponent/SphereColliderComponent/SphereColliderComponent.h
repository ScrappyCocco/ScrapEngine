#pragma once

#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SphereColliderComponent : public ColliderComponent
		{
		public:
			SphereColliderComponent(Physics::RigidBody* rigidbody);
			~SphereColliderComponent() = default;
		};
	}
}
