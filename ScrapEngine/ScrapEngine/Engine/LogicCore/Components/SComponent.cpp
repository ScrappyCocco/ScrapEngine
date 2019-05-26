#include <Engine/LogicCore/Components/SComponent.h>

ScrapEngine::Core::SComponent::SComponent(const std::string& component_name) : SObject(component_name)
{
}

ScrapEngine::Core::SComponent::~SComponent()
{
	//Empty here
}

void ScrapEngine::Core::SComponent::set_component_location(const glm::vec3& location)
{
	object_world_transform_.location = location;
	object_relative_transform_.location = object_world_transform_.location - father_transform_.location;
}

void ScrapEngine::Core::SComponent::set_component_rotation(const glm::vec3& rotation)
{
	object_world_transform_.rotation = rotation;
}

void ScrapEngine::Core::SComponent::set_component_scale(const glm::vec3& scale)
{
	object_world_transform_.scale = scale;
}

void ScrapEngine::Core::SComponent::update_component_location()
{
	object_world_transform_.location = father_transform_.location + object_relative_transform_.location;
}

void ScrapEngine::Core::SComponent::set_father_transform(const Transform& input_father_transform)
{
	father_transform_ = input_father_transform;
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_location() const
{
	return object_world_transform_.location;
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_rotation() const
{
	return object_world_transform_.rotation;
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_scale() const
{
	return object_world_transform_.scale;
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_relative_location() const
{
	return object_relative_transform_.location;
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_relative_rotation() const
{
	return object_relative_transform_.rotation;
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_relative_scale() const
{
	return object_relative_transform_.scale;
}
