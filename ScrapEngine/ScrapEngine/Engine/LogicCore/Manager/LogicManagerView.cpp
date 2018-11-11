#include "LogicManagerView.h"

ScrapEngine::LogicManagerView::LogicManagerView(ScrapEngine::RenderManager* input_RenderManagerRef, ScrapEngine::LogicManager* input_LogicManagerRef)
	: RenderManagerRef(input_RenderManagerRef), LogicManagerRef(input_LogicManagerRef)
{
	ComponentManager = new ComponentsManager(input_RenderManagerRef);
	SceneManager = new ScrapEngine::SceneManager(input_RenderManagerRef);
}

ScrapEngine::LogicManagerView::~LogicManagerView()
{
	delete ComponentManager;
}

ScrapEngine::SGameObject* ScrapEngine::LogicManagerView::RegisterGameObject(SGameObject* input_GameObject)
{
	return LogicManagerRef->RegisterGameObject(input_GameObject);
}

void ScrapEngine::LogicManagerView::UnRegisterGameObject(SGameObject* input_GameObject)
{
	LogicManagerRef->UnRegisterGameObject(input_GameObject);
}

ScrapEngine::ComponentsManager* ScrapEngine::LogicManagerView::getComponentsManager() const
{
	return ComponentManager;
}

ScrapEngine::SceneManager* ScrapEngine::LogicManagerView::getSceneManager() const
{
	return SceneManager;
}
