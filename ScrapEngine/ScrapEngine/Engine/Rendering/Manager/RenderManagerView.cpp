#include <Engine/Rendering/Manager/RenderManagerView.h>

ScrapEngine::Render::RenderManagerView::
RenderManagerView(RenderManager* input_render_manager_ref)
	: render_manager_ref_(input_render_manager_ref)
{
}

ScrapEngine::Render::GameWindow* ScrapEngine::Render::RenderManagerView::get_game_window() const
{
	return render_manager_ref_->get_game_window();
}
