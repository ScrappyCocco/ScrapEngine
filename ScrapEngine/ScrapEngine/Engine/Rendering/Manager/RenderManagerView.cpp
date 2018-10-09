#include "RenderManagerView.h"

ScrapEngine::RenderManagerView::RenderManagerView(ScrapEngine::RenderManager* input_RenderManagerRef) : RenderManagerRef(input_RenderManagerRef)
{

}

ScrapEngine::GameWindow* ScrapEngine::RenderManagerView::getGameWindow() const
{
	return RenderManagerRef->getGameWindow();
}

