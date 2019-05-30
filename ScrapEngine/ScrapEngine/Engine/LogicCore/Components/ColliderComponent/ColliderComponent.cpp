#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

ScrapEngine::Core::ColliderComponent::ColliderComponent(Physics::RigidBody* rigidbody)
	:SComponent("ColliderComponent"), rigidbody_(rigidbody)
{
}

ScrapEngine::Core::ColliderComponent::~ColliderComponent()
{
	delete rigidbody_;
}
