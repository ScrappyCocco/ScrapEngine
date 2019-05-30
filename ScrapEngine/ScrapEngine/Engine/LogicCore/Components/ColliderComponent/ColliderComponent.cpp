#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>

ScrapEngine::Core::ColliderComponent::ColliderComponent(Physics::RigidBody* rigidbody)
	:SComponent("ColliderComponent"), rigidbody_(rigidbody)
{
}

ScrapEngine::Core::ColliderComponent::~ColliderComponent()
{
	delete rigidbody_;
}

void ScrapEngine::Core::ColliderComponent::attach_to_mesh(MeshComponent* mesh)
{
	attached_mesh_ = mesh;
}

void ScrapEngine::Core::ColliderComponent::update_transform(const float factor) const
{
	if (attached_mesh_) {
		const STransform new_transform = rigidbody_->get_updated_transform(factor);

		attached_mesh_->set_component_location(new_transform.get_position());
		attached_mesh_->set_component_rotation(new_transform.get_rotation());
	}
}
