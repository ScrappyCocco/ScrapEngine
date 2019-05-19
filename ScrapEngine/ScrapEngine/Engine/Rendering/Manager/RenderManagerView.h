#pragma once
#include <Engine/Rendering/Manager/RenderManager.h>

namespace ScrapEngine
{
	namespace Render
	{
		class RenderManagerView
		{
		private:
			ScrapEngine::Render::RenderManager* render_manager_ref_;
		public:
			RenderManagerView(ScrapEngine::Render::RenderManager* input_render_manager_ref);
			~RenderManagerView() = default;

			ScrapEngine::Render::GameWindow* get_game_window() const;

			ScrapEngine::Render::Camera* get_default_render_camera() const;
			ScrapEngine::Render::Camera* get_current_render_camera() const;
			void set_render_camera(ScrapEngine::Render::Camera*) const;
		};
	}
}
