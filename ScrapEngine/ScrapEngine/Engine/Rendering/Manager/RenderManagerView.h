#pragma once
#include "RenderManager.h"

namespace ScrapEngine {
	namespace Render {
		class RenderManagerView
		{
		private:
			ScrapEngine::Render::RenderManager* RenderManagerRef;
		public:
			RenderManagerView(ScrapEngine::Render::RenderManager* input_RenderManagerRef);
			~RenderManagerView() = default;

			ScrapEngine::Render::GameWindow* getGameWindow() const;

			ScrapEngine::Camera* getDefaultRenderCamera() const;
			ScrapEngine::Camera* getCurrentRenderCamera() const;
			void setRenderCamera(ScrapEngine::Camera*) const;
		};
	}
}

