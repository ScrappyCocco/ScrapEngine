#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>

ScrapEngine::Core::RigidBodyComponent::RigidBodyComponent(Physics::RigidBody* rigidbody)
	:SComponent("ColliderComponent"), rigidbody_(rigidbody)
{
}

ScrapEngine::Core::RigidBodyComponent::~RigidBodyComponent()
{
	delete rigidbody_;
}

void ScrapEngine::Core::RigidBodyComponent::attach_to_mesh(MeshComponent* mesh)
{
	attached_mesh_ = mesh;
}

void ScrapEngine::Core::RigidBodyComponent::update_transform(const float factor) const
{
	if (attached_mesh_) {
		const STransform new_transform = rigidbody_->get_updated_transform(factor);

		attached_mesh_->set_component_location(new_transform.get_position());
		attached_mesh_->set_component_rotation(new_transform.get_rotation());
	}
}

void ScrapEngine::Core::RigidBodyComponent::set_rigidbody_type(Physics::RigidBody_Types type) const
{
	rigidbody_->set_type(type);
}
