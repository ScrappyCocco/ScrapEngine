#include "SceneManager.h"

ScrapEngine::Core::SceneManager::SceneManager(ScrapEngine::Render::RenderManager* input_render_manager_ref) : render_manager_ref_(input_render_manager_ref),
                                                                     current_skybox_(nullptr)
{
}

void ScrapEngine::Core::SceneManager::set_skybox(const std::array<std::string, 6>& files_path)
{
	current_skybox_ = render_manager_ref_->loadSkybox(files_path);
}

void ScrapEngine::Core::SceneManager::set_skybox_size(const unsigned int new_size) const
{
	if (current_skybox_)
	{
		current_skybox_->setCubemapSize(new_size);
	}
}
