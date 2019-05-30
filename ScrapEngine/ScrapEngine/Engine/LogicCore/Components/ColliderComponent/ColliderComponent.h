#pragma once

#include "Engine/LogicCore/Components/SComponent.h"
#include <Engine/Physics/RigidBody/RigidBody.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ColliderComponent : public SComponent
		{
		private:
			Physics::RigidBody* rigidbody_ = nullptr;
		public:
			ColliderComponent(Physics::RigidBody* rigidbody);
			virtual ~ColliderComponent();
		};
	}
}
