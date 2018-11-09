#include "SceneManager.h"

ScrapEngine::SceneManager::SceneManager(ScrapEngine::RenderManager* input_RenderManagerRef) : RenderManagerRef(input_RenderManagerRef)
{

}

ScrapEngine::SceneManager::~SceneManager()
{
}

void ScrapEngine::SceneManager::setSkybox(const std::array<std::string, 6>& files_path)
{
	CurrentSkybox = RenderManagerRef->loadSkybox(files_path);
}

void ScrapEngine::SceneManager::setSkyboxSize(unsigned int newSize)
{
	if (CurrentSkybox) {
		CurrentSkybox->setCubemapSize(newSize);
	}
}
