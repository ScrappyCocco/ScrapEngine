#pragma once

#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>


namespace ScrapEngine
{
	namespace Core
	{
		class BoxRigidBodyComponent : public RigidBodyComponent
		{
		public:
			BoxRigidBodyComponent(Physics::RigidBody* rigidbody);
			~BoxRigidBodyComponent() = default;
		};
	}
}
