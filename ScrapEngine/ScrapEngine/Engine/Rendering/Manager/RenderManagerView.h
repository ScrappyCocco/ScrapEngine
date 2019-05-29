#pragma once
#include <Engine/Rendering/Manager/RenderManager.h>

namespace ScrapEngine
{
	namespace Render
	{
		class RenderManagerView
		{
		private:
			RenderManager* render_manager_ref_;
		public:
			RenderManagerView(RenderManager* input_render_manager_ref);
			~RenderManagerView() = default;

			GameWindow* get_game_window() const;

			Camera* get_default_render_camera() const;
			Camera* get_current_render_camera() const;
			void set_render_camera(Camera*) const;
		};
	}
}
