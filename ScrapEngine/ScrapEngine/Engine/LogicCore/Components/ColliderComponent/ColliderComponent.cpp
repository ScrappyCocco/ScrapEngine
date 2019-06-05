#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

ScrapEngine::Core::ColliderComponent::ColliderComponent(Physics::CollisionBody* collisionbody)
	:SComponent("ColliderComponent"), collisionbody_(collisionbody)
{
}

ScrapEngine::Core::ColliderComponent::~ColliderComponent()
{
	delete collisionbody_;
}

void ScrapEngine::Core::ColliderComponent::set_component_location(const SVector3& location)
{
	SComponent::set_component_location(location);
	collisionbody_->update_trasform(get_component_transform());
}

void ScrapEngine::Core::ColliderComponent::set_component_rotation(const SVector3& rotation)
{
	SComponent::set_component_rotation(rotation);
	collisionbody_->update_trasform(get_component_transform());
}


