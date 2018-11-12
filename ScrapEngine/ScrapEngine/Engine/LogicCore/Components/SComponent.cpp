#include "SComponent.h"

ScrapEngine::SComponent::SComponent(const std::string& componentName) : SObject(componentName)
{

}

ScrapEngine::SComponent::~SComponent()
{
	//Empty here
}

void ScrapEngine::SComponent::setComponentLocation(const glm::vec3& location)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SComponent::setComponentRotation(const glm::vec3& rotation)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SComponent::setComponentScale(const glm::vec3& scale)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

glm::vec3 ScrapEngine::SComponent::getComponentLocation() const
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}

glm::vec3 ScrapEngine::SComponent::getComponentRotation() const
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}

glm::vec3 ScrapEngine::SComponent::getComponentScale() const
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}
