#include "RenderManagerView.h"

ScrapEngine::RenderManagerView::RenderManagerView(ScrapEngine::RenderManager* input_RenderManagerRef) : RenderManagerRef(input_RenderManagerRef)
{

}

ScrapEngine::GameWindow* ScrapEngine::RenderManagerView::getGameWindow() const
{
	return RenderManagerRef->getGameWindow();
}

ScrapEngine::Camera * ScrapEngine::RenderManagerView::getRenderCamera() const
{
	return RenderManagerRef->getRenderCamera();
}

