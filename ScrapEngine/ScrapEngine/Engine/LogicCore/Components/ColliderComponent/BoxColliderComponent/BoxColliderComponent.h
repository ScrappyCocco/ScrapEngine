#pragma once

#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class BoxColliderComponent : public ColliderComponent
		{
		public:
			BoxColliderComponent(Physics::RigidBody* rigidbody);
			~BoxColliderComponent() = default;
		};
	}
}
