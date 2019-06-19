#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>

ScrapEngine::Core::RigidBodyComponent::RigidBodyComponent(Physics::RigidBody* rigidbody)
	: SComponent("ColliderComponent"), rigidbody_(rigidbody)
{
}

ScrapEngine::Core::RigidBodyComponent::~RigidBodyComponent()
{
	delete rigidbody_;
}

void ScrapEngine::Core::RigidBodyComponent::set_component_location(const SVector3& location)
{
	const Physics::RigidBody_Types type = rigidbody_->get_type();
	if (type == Physics::RigidBody_Types::static_rigidbody || type == Physics::RigidBody_Types::kinematic_rigidbody)
	{
		SComponent::set_component_location(location);
		rigidbody_->set_new_transform(get_component_transform());
	}
}

void ScrapEngine::Core::RigidBodyComponent::set_component_rotation(const SVector3& rotation)
{
	const Physics::RigidBody_Types type = rigidbody_->get_type();
	if (type == Physics::RigidBody_Types::static_rigidbody || type == Physics::RigidBody_Types::kinematic_rigidbody)
	{
		SComponent::set_component_rotation(rotation);
		rigidbody_->set_new_transform(get_component_transform());
	}
}

void ScrapEngine::Core::RigidBodyComponent::attach_to_mesh(MeshComponent* mesh)
{
	attached_mesh_ = mesh;
}

void ScrapEngine::Core::RigidBodyComponent::update_transform(const float factor) const
{
	if (attached_mesh_)
	{
		const STransform new_transform = rigidbody_->get_updated_transform(factor);

		attached_mesh_->set_component_location(new_transform.get_position());
		attached_mesh_->set_component_rotation(new_transform.get_rotation());
	}
}

void ScrapEngine::Core::RigidBodyComponent::set_rigidbody_type(const Physics::RigidBody_Types type) const
{
	rigidbody_->set_type(type);
}

float ScrapEngine::Core::RigidBodyComponent::get_bounciness() const
{
	return rigidbody_->get_bounciness();
}

void ScrapEngine::Core::RigidBodyComponent::set_bounciness(const float bounce_factor) const
{
	rigidbody_->set_bounciness(bounce_factor);
}

float ScrapEngine::Core::RigidBodyComponent::get_friction_coefficient() const
{
	return rigidbody_->get_friction_coefficient();
}

void ScrapEngine::Core::RigidBodyComponent::set_friction_coefficient(const float coefficient) const
{
	rigidbody_->set_friction_coefficient(coefficient);
}

void ScrapEngine::Core::RigidBodyComponent::apply_force_to_center(const SVector3& force) const
{
	rigidbody_->apply_force_to_center(force);
}
