#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

ScrapEngine::Core::RigidBodyComponent::RigidBodyComponent(Physics::RigidBody* rigidbody)
	: SComponent("RigidbodyComponent"), rigidbody_(rigidbody)
{
}

ScrapEngine::Core::RigidBodyComponent::~RigidBodyComponent()
{
	delete rigidbody_;
}

void ScrapEngine::Core::RigidBodyComponent::set_component_location(const SVector3& location)
{
	const Physics::RigidBody_Types type = rigidbody_->get_type();
	if (type == Physics::RigidBody_Types::static_rigidbody)
	{
		SComponent::set_component_location(location);
		rigidbody_->set_new_transform(get_component_transform());
	}
}

void ScrapEngine::Core::RigidBodyComponent::set_component_rotation(const SVector3& rotation)
{
	const Physics::RigidBody_Types type = rigidbody_->get_type();
	if (type == Physics::RigidBody_Types::static_rigidbody)
	{
		SComponent::set_component_rotation(rotation);
		rigidbody_->set_new_transform(get_component_transform());
	}
}

void ScrapEngine::Core::RigidBodyComponent::modify_rigidbody_location(const SVector3& location) const
{
	rigidbody_->set_new_location(location);
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

		if (update_mesh_position_) {
			attached_mesh_->set_component_location(new_transform.get_position());
		}
		if (update_mesh_rotation_) {
			attached_mesh_->set_component_rotation(new_transform.get_rotation());
		}
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

bool ScrapEngine::Core::RigidBodyComponent::get_allowed_to_sleep() const
{
	return rigidbody_->get_allowed_to_sleep();
}

void ScrapEngine::Core::RigidBodyComponent::set_allowed_to_sleep(const bool allowed) const
{
	rigidbody_->set_allowed_to_sleep(allowed);
}

void ScrapEngine::Core::RigidBodyComponent::apply_force_to_center(const SVector3& force) const
{
	rigidbody_->apply_force_to_center(force);
}

void ScrapEngine::Core::RigidBodyComponent::apply_torqe(const SVector3& force) const
{
	rigidbody_->apply_torque(force);
}

void ScrapEngine::Core::RigidBodyComponent::cancel_rigidbody_forces() const
{
	rigidbody_->cancel_rigidbody_forces();
}

void ScrapEngine::Core::RigidBodyComponent::set_update_mesh_position(const bool update)
{
	update_mesh_position_ = update;
}

void ScrapEngine::Core::RigidBodyComponent::set_update_mesh_rotation(const bool update)
{
	update_mesh_rotation_ = update;
}
