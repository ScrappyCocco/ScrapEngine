#include <Engine/LogicCore/Manager/LogicManagerView.h>

ScrapEngine::Core::LogicManagerView::LogicManagerView(ScrapEngine::Render::RenderManager* input_render_manager_ref,
                                                      ScrapEngine::Core::LogicManager* input_logic_manager_ref)
	: logic_manager_ref_(input_logic_manager_ref)
{
	component_manager_ = new ComponentsManager(input_render_manager_ref);
	scene_manager_ = new ScrapEngine::Core::SceneManager(input_render_manager_ref);
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

ScrapEngine::Core::ComponentsManager* ScrapEngine::Core::LogicManagerView::get_components_manager() const
{
	return component_manager_;
}

ScrapEngine::Core::SceneManager* ScrapEngine::Core::LogicManagerView::get_scene_manager() const
{
	return scene_manager_;
}
