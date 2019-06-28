#pragma once

#include <Engine/LogicCore/Components/TriggerComponent/TriggerComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class BoxTriggerComponent : public TriggerComponent
		{
		public:
			BoxTriggerComponent(Physics::CollisionBody* collisionbody);
			~BoxTriggerComponent() = default;
		};
	}
}
