#include "RenderManagerView.h"

ScrapEngine::Render::RenderManagerView::RenderManagerView(ScrapEngine::Render::RenderManager* input_RenderManagerRef) : RenderManagerRef(input_RenderManagerRef)
{

}

ScrapEngine::Render::GameWindow* ScrapEngine::Render::RenderManagerView::getGameWindow() const
{
	return RenderManagerRef->getGameWindow();
}

ScrapEngine::Camera * ScrapEngine::Render::RenderManagerView::getDefaultRenderCamera() const
{
	return RenderManagerRef->getDefaultRenderCamera();
}

ScrapEngine::Camera * ScrapEngine::Render::RenderManagerView::getCurrentRenderCamera() const
{
	return RenderManagerRef->getRenderCamera();
}

void ScrapEngine::Render::RenderManagerView::setRenderCamera(ScrapEngine::Camera* newCamera) const
{
	RenderManagerRef->setRenderCamera(newCamera);
}

