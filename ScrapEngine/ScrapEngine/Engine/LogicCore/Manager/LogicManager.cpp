#include "LogicManager.h"

ScrapEngine::LogicManager::LogicManager()
{

}

ScrapEngine::LogicManager::~LogicManager()
{
	for (SGameObject* GameObject : RegisteredGameObjects) {
		delete GameObject;
	}
}

ScrapEngine::SGameObject* ScrapEngine::LogicManager::RegisterGameObject(SGameObject* input_GameObject)
{
	RegisteredGameObjects.push_back(input_GameObject);
	return RegisteredGameObjects.back();
}

void ScrapEngine::LogicManager::UnRegisterGameObject(SGameObject* input_GameObject)
{
	std::vector<SGameObject*>::iterator element = find(RegisteredGameObjects.begin(), RegisteredGameObjects.end(), input_GameObject);
	if (element != RegisteredGameObjects.end())
	{
		delete *element;
		RegisteredGameObjects.erase(element);
	}
}

void ScrapEngine::LogicManager::ExecuteGameObjectsStartEvent()
{
	for (SGameObject* GameObject : RegisteredGameObjects) {
		GameObject->GameStart();
	}
}

void ScrapEngine::LogicManager::ExecuteGameObjectsUpdateEvent()
{
	for (SGameObject* GameObject : RegisteredGameObjects) {
		GameObject->GameUpdate();
	}
}
