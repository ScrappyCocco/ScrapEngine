#pragma once

#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SphereColliderComponent : public ColliderComponent
		{
		public:
			SphereColliderComponent(Physics::CollisionBody* collisionbody);
			~SphereColliderComponent() = default;
		};
	}
}
