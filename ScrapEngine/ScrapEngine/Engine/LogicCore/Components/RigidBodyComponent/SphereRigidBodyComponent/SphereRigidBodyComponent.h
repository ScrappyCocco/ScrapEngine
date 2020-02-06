#pragma once

#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SphereRigidBodyComponent : public RigidBodyComponent
		{
		public:
			SphereRigidBodyComponent(Physics::RigidBody* rigidbody);
			~SphereRigidBodyComponent() = default;
		};
	}
}
