#include <Engine/LogicCore/Components/SComponent.h>
#include <glm/mat4x4.hpp>

ScrapEngine::Core::SComponent::SComponent(const std::string& component_name) : SObject(component_name)
{
}

ScrapEngine::Core::SComponent::~SComponent()
{
	//Empty here
}

void ScrapEngine::Core::SComponent::set_component_location(const ScrapEngine::Core::SVector3& location)
{
	object_world_transform_.set_position(location);
	object_relative_transform_.set_position(object_world_transform_.get_position() - father_transform_.get_position());
}

void ScrapEngine::Core::SComponent::set_component_rotation(const ScrapEngine::Core::SVector3& rotation)
{
	object_world_transform_.set_rotation(rotation);
	object_relative_transform_.set_rotation(object_world_transform_.get_rotation() - father_transform_.get_rotation());
}

void ScrapEngine::Core::SComponent::set_component_scale(const ScrapEngine::Core::SVector3& scale)
{
	object_world_transform_.set_scale(scale);
	object_relative_transform_.set_scale(object_world_transform_.get_scale() - father_transform_.get_scale());
}

void ScrapEngine::Core::SComponent::update_relative_transform()
{
	object_relative_transform_.set_position(object_world_transform_.get_position() - father_transform_.get_position());
	object_relative_transform_.set_rotation(object_world_transform_.get_rotation() - father_transform_.get_rotation());
	object_relative_transform_.set_scale(object_world_transform_.get_scale() - father_transform_.get_scale());
}

void ScrapEngine::Core::SComponent::update_component_location()
{
	const glm::mat4 local_m = generate_unscaled_transform_matrix(object_relative_transform_);
	const glm::mat4 father_m = generate_unscaled_transform_matrix(father_transform_);
	glm::mat4 full_m = father_m * local_m;

	glm::vec3 pos = glm::vec3(full_m[3][0], full_m[3][1], full_m[3][2]);

	object_world_transform_.set_position(SVector3(pos));
}

void ScrapEngine::Core::SComponent::update_component_rotation()
{
	object_world_transform_.set_rotation(father_transform_.get_rotation() + object_relative_transform_.get_rotation());

	update_component_location();
}

void ScrapEngine::Core::SComponent::update_component_scale()
{
	object_world_transform_.set_scale(father_transform_.get_scale() + object_relative_transform_.get_scale());
}

void ScrapEngine::Core::SComponent::set_father_transform(const STransform& input_father_transform)
{
	father_transform_ = input_father_transform;
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
