#pragma once

#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class CapsuleColliderComponent : public ColliderComponent
		{
		public:
			CapsuleColliderComponent(Physics::CollisionBody* collisionbody);
			~CapsuleColliderComponent() = default;
		};
	}
}
