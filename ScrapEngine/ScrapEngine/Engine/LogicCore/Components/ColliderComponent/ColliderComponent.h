#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/Physics/RigidBody/RigidBody.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ColliderComponent : public SComponent
		{
		private:
			Physics::RigidBody* rigidbody_ = nullptr;

			MeshComponent* attached_mesh_ = nullptr;
		public:
			ColliderComponent(Physics::RigidBody* rigidbody);
			virtual ~ColliderComponent();

			void attach_to_mesh(MeshComponent* mesh);
			void update_transform(float factor) const;
			void set_rigidbody_type(Physics::RigidBody_Types type) const;
		};
	}
}
