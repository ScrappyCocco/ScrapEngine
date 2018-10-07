#include "SComponent.h"

ScrapEngine::SComponent::SComponent(std::string componentName, SGameObject * ComponentParent) : SObject(componentName), Parent(ComponentParent)
{

}

ScrapEngine::SComponent::~SComponent()
{
	//Empty here
}
