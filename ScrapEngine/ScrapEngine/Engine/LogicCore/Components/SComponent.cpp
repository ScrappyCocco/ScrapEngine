#include "SComponent.h"

ScrapEngine::SComponent::SComponent(std::string componentName) : SObject(componentName)
{

}

ScrapEngine::SComponent::~SComponent()
{
	//Empty here
}

void ScrapEngine::SComponent::setComponentLocation(glm::vec3 location)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SComponent::setComponentRotation(glm::vec3 rotation)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SComponent::setComponentScale(glm::vec3 scale)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

glm::vec3 ScrapEngine::SComponent::getComponentLocation()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}

glm::vec3 ScrapEngine::SComponent::getComponentRotation()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}

glm::vec3 ScrapEngine::SComponent::getComponentScale()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
	return glm::vec3();
}
