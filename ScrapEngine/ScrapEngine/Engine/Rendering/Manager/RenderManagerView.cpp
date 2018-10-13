#include "RenderManagerView.h"

ScrapEngine::RenderManagerView::RenderManagerView(ScrapEngine::RenderManager* input_RenderManagerRef) : RenderManagerRef(input_RenderManagerRef)
{

}

ScrapEngine::GameWindow* ScrapEngine::RenderManagerView::getGameWindow() const
{
	return RenderManagerRef->getGameWindow();
}

ScrapEngine::Camera * ScrapEngine::RenderManagerView::getDefaultRenderCamera() const
{
	return RenderManagerRef->getDefaultRenderCamera();
}

ScrapEngine::Camera * ScrapEngine::RenderManagerView::getCurrentRenderCamera() const
{
	return RenderManagerRef->getRenderCamera();
}

void ScrapEngine::RenderManagerView::setRenderCamera(ScrapEngine::Camera* newCamera) const
{
	RenderManagerRef->setRenderCamera(newCamera);
}

