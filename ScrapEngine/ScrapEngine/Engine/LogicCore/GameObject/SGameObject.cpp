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
	//Empty here
}

void ScrapEngine::SGameObject::GameUpdate()
{
	//Empty here
}

void ScrapEngine::SGameObject::AddComponent(SComponent* Component)
{
	ObjectComponents.push_back(Component);
}

const std::vector<ScrapEngine::SComponent*>* ScrapEngine::SGameObject::GetComponents()
{
	return &ObjectComponents;
}
