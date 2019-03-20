#include "LogicManagerView.h"

ScrapEngine::Core::LogicManagerView::LogicManagerView(ScrapEngine::RenderManager* input_RenderManagerRef,
                                                      ScrapEngine::Core::LogicManager* input_LogicManagerRef)
	: render_manager_ref_(input_RenderManagerRef), logic_manager_ref_(input_LogicManagerRef)
{
	component_manager_ = new ComponentsManager(input_RenderManagerRef);
	scene_manager_ = new ScrapEngine::Core::SceneManager(input_RenderManagerRef);
}

ScrapEngine::Core::LogicManagerView::~LogicManagerView()
{
	delete component_manager_;
}

ScrapEngine::Core::SGameObject* ScrapEngine::Core::LogicManagerView::register_game_object(
	ScrapEngine::Core::SGameObject* input_game_object) const
{
	return logic_manager_ref_->register_game_object(input_game_object);
}

void ScrapEngine::Core::LogicManagerView::un_register_game_object(
	ScrapEngine::Core::SGameObject* input_game_object) const
{
	logic_manager_ref_->un_register_game_object(input_game_object);
}

ScrapEngine::Core::ComponentsManager* ScrapEngine::Core::LogicManagerView::getComponentsManager() const
{
	return component_manager_;
}

ScrapEngine::Core::SceneManager* ScrapEngine::Core::LogicManagerView::getSceneManager() const
{
	return scene_manager_;
}
