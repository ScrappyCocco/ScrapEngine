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
		ScrapEngine::Camera* getRenderCamera() const;
	};

}

