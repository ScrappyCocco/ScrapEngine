#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/Physics/CollisionBody/CollisionBody.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ColliderComponent : public SComponent
		{
		private:
			Physics::CollisionBody* collisionbody_ = nullptr;

			MeshComponent* attached_mesh_ = nullptr;
		public:
			ColliderComponent(Physics::CollisionBody* collisionbody);
			virtual ~ColliderComponent();

			void set_component_location(const SVector3& location) override;
			void set_component_rotation(const SVector3& rotation) override;
		};
	}
}
