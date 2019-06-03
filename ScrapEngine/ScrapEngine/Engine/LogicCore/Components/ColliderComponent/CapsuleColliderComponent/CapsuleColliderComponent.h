#pragma once

#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class CapsuleColliderComponent : public ColliderComponent
		{
		public:
			CapsuleColliderComponent(Physics::RigidBody* rigidbody);
			~CapsuleColliderComponent() = default;
		};
	}
}
