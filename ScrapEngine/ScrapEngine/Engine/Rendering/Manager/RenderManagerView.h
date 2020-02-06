#pragma once

namespace ScrapEngine
{
	namespace Render
	{
		class RenderManager;
		class GameWindow;

		class RenderManagerView
		{
		private:
			RenderManager* render_manager_ref_;
		public:
			RenderManagerView(RenderManager* input_render_manager_ref);
			~RenderManagerView() = default;

			GameWindow* get_game_window() const;
		};
	}
}
