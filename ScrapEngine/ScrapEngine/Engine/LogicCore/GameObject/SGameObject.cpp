#include "SGameObject.h"

ScrapEngine::SGameObject::SGameObject(std::string objectName, ScrapEngine::Transform input_ObjectTransform, bool isStaticObject) : 
	SObject(objectName), ObjectTransform(input_ObjectTransform), isStatic(isStaticObject)
{
}

ScrapEngine::SGameObject::~SGameObject()
{
	for (SComponent* component : ObjectComponents) {
		delete component;
	}
}

void ScrapEngine::SGameObject::GameStart()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SGameObject::GameUpdate()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SGameObject::setObjectLocation(glm::vec3 location)
{
	ObjectTransform.location = location;
	//Update the transform of every component
	for (SComponent* component : ObjectComponents) {
		component->setComponentLocation(location);
	}
}

void ScrapEngine::SGameObject::setObjectRotation(glm::vec3 rotation)
{
	ObjectTransform.rotation = rotation;
	//Update the transform of every component
	for (SComponent* component : ObjectComponents) {
		component->setComponentRotation(rotation);
	}
}

void ScrapEngine::SGameObject::setObjectScale(glm::vec3 scale)
{
	ObjectTransform.scale = scale;
	//Update the transform of every component
	for (SComponent* component : ObjectComponents) {
		component->setComponentScale(scale);
	}
}

glm::vec3 ScrapEngine::SGameObject::getObjectLocation()
{
	return ObjectTransform.location;
}

glm::vec3 ScrapEngine::SGameObject::getObjectRotation()
{
	return ObjectTransform.rotation;
}

glm::vec3 ScrapEngine::SGameObject::getObjectScale()
{
	return ObjectTransform.scale;
}

void ScrapEngine::SGameObject::AddComponent(SComponent* Component)
{
	ObjectComponents.push_back(Component);
}

const std::vector<ScrapEngine::SComponent*>* ScrapEngine::SGameObject::GetComponents()
{
	return &ObjectComponents;
}
