#pragma once

#include <Engine/LogicCore/Components/SComponent.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class CollisionBody;
	}
}

namespace ScrapEngine
{
	namespace Core
	{
		class RigidBodyComponent;

		class TriggerComponent : public SComponent
		{
		private:
			Physics::CollisionBody* collisionbody_ = nullptr;
		public:
			TriggerComponent(Physics::CollisionBody* collisionbody);
			virtual ~TriggerComponent() = 0;

			void set_component_location(const SVector3& location) override;
			void set_component_rotation(const SVector3& rotation) override;

			bool test_collision(TriggerComponent* other) const;
			bool test_collision(RigidBodyComponent* other) const;
		};
	}
}
