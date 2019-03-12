#include "SGameObject.h"

ScrapEngine::SGameObject::SGameObject(const std::string& objectName, const ScrapEngine::Transform& input_ObjectTransform, bool isStaticObject) :
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

void ScrapEngine::SGameObject::GameUpdate(float time)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::SGameObject::setObjectLocation(const glm::vec3& location)
{
	ObjectTransform.location = location;
	//Update the transform of every component
	for (SComponent* component : ObjectComponents) {
		component->setComponentLocation(location);
	}
}

void ScrapEngine::SGameObject::setObjectRotation(const glm::vec3& rotation)
{
	ObjectTransform.rotation = rotation;
	//Update the transform of every component
	for (SComponent* component : ObjectComponents) {
		component->setComponentRotation(rotation);
	}
}

void ScrapEngine::SGameObject::setObjectScale(const glm::vec3& scale)
{
	ObjectTransform.scale = scale;
	//Update the transform of every component
	for (SComponent* component : ObjectComponents) {
		component->setComponentScale(scale);
	}
}

glm::vec3 ScrapEngine::SGameObject::getObjectLocation() const
{
	return ObjectTransform.location;
}

glm::vec3 ScrapEngine::SGameObject::getObjectRotation() const
{
	return ObjectTransform.rotation;
}

glm::vec3 ScrapEngine::SGameObject::getObjectScale() const
{
	return ObjectTransform.scale;
}

void ScrapEngine::SGameObject::AddComponent(SComponent* Component)
{
	ObjectComponents.push_back(Component);
	//Set component default values same as object
	Component->setComponentLocation(ObjectTransform.location);
	Component->setComponentRotation(ObjectTransform.rotation);
	Component->setComponentScale(ObjectTransform.scale);
}

const std::vector<ScrapEngine::SComponent*>* ScrapEngine::SGameObject::GetComponents()
{
	return &ObjectComponents;
}
