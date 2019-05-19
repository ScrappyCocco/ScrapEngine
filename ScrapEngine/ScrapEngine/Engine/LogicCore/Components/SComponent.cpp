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
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SComponent::set_component_rotation(const glm::vec3& rotation)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SComponent::set_component_scale(const glm::vec3& scale)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_location() const
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_rotation() const
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}

glm::vec3 ScrapEngine::Core::SComponent::get_component_scale() const
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}
