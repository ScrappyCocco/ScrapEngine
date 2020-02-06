#pragma once

#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class CapsuleRigidBodyComponent : public RigidBodyComponent
		{
		public:
			CapsuleRigidBodyComponent(Physics::RigidBody* rigidbody);
			~CapsuleRigidBodyComponent() = default;
		};
	}
}
