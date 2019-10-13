#include <Engine/LogicCore/Components/SComponent.h>
#include <glm/mat4x4.hpp>

ScrapEngine::Core::SComponent::SComponent(const std::string& component_name) : SObject(component_name)
{
}

ScrapEngine::Core::SComponent::~SComponent()
{
	//Empty here
}

void ScrapEngine::Core::SComponent::set_component_location(const SVector3& location)
{
	object_world_transform_.set_position(location);
	update_relative_location();
}

void ScrapEngine::Core::SComponent::set_component_rotation(const SVector3& rotation)
{
	object_world_transform_.set_rotation(rotation);
	update_relative_rotation();
}

void ScrapEngine::Core::SComponent::set_component_scale(const SVector3& scale)
{
	object_world_transform_.set_scale(scale);
	update_relative_scale();
}

void ScrapEngine::Core::SComponent::add_component_rotation(const SVector3& rotation)
{
	object_world_transform_.add_rotation(rotation);
	update_relative_rotation();
}

void ScrapEngine::Core::SComponent::update_component_location()
{
	const glm::mat4 local_m = generate_unscaled_transform_matrix(object_relative_transform_);
	const glm::mat4 father_m = generate_unscaled_transform_matrix(owner_->object_transform_);
	glm::mat4 full_m = father_m * local_m;

	const glm::vec3 pos = glm::vec3(full_m[3][0], full_m[3][1], full_m[3][2]);

	object_world_transform_.set_position(SVector3(pos));
}

void ScrapEngine::Core::SComponent::update_component_rotation()
{
	object_world_transform_.set_rotation(
		owner_->object_transform_.get_quat_rotation() * object_relative_transform_.get_quat_rotation()
	);

	update_component_location();
}

void ScrapEngine::Core::SComponent::update_component_scale()
{
	object_world_transform_.set_scale(owner_->object_transform_.get_scale() + object_relative_transform_.get_scale());
}

ScrapEngine::Core::STransform ScrapEngine::Core::SComponent::get_component_transform() const
{
	return object_world_transform_;
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SComponent::get_component_location() const
{
	return object_world_transform_.get_position();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SComponent::get_component_rotation() const
{
	return object_world_transform_.get_rotation();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SComponent::get_component_scale() const
{
	return object_world_transform_.get_scale();
}

ScrapEngine::Core::SGameObject* ScrapEngine::Core::SComponent::get_owner() const
{
	return owner_;
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SComponent::get_component_relative_location() const
{
	return object_relative_transform_.get_position();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SComponent::get_component_relative_rotation() const
{
	return object_relative_transform_.get_rotation();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SComponent::get_component_relative_scale() const
{
	return object_relative_transform_.get_scale();
}

void ScrapEngine::Core::SComponent::update_relative_location()
{
	if (owner_)
	{
		object_relative_transform_.set_position(
			object_world_transform_.get_position() - owner_->object_transform_.get_position());
	}
}

void ScrapEngine::Core::SComponent::update_relative_rotation()
{
	if (owner_)
	{
		object_relative_transform_.set_rotation(
			owner_->object_transform_.get_quat_rotation().get_inverse() * object_world_transform_.get_quat_rotation()
		);
	}
}

void ScrapEngine::Core::SComponent::update_relative_scale()
{
	if (owner_)
	{
		object_relative_transform_.set_scale(
			object_world_transform_.get_scale() - owner_->object_transform_.get_scale());
	}
}
