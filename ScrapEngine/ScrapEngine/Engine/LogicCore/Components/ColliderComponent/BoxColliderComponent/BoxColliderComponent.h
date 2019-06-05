#pragma once

#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class BoxColliderComponent : public ColliderComponent
		{
		public:
			BoxColliderComponent(Physics::CollisionBody* collisionbody);
			~BoxColliderComponent() = default;
		};
	}
}
