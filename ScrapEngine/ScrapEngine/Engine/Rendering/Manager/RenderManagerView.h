#pragma once
#include "RenderManager.h"

namespace ScrapEngine {

	class RenderManagerView
	{
	private:
		ScrapEngine::RenderManager* RenderManagerRef;
	public:
		RenderManagerView(ScrapEngine::RenderManager* input_RenderManagerRef);
		~RenderManagerView() = default;

		ScrapEngine::GameWindow* getGameWindow() const;

		ScrapEngine::Camera* getDefaultRenderCamera() const;
		ScrapEngine::Camera* getCurrentRenderCamera() const;
		void setRenderCamera(ScrapEngine::Camera*) const;
	};

}

