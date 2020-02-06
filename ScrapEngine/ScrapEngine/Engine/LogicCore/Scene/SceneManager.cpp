#include <Engine/LogicCore/Scene/SceneManager.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>

ScrapEngine::Core::SceneManager::SceneManager(Render::RenderManager* input_render_manager_ref) :
	render_manager_ref_(input_render_manager_ref)
{
	shadowmapping_manager_ = render_manager_ref_->get_shadowmapping_manager();
}

void ScrapEngine::Core::SceneManager::set_skybox(const std::array<std::string, 6>& files_path)
{
	current_skybox_ = render_manager_ref_->load_skybox(files_path);
}

void ScrapEngine::Core::SceneManager::set_skybox_size(const unsigned int new_size) const
{
	if (current_skybox_)
	{
		current_skybox_->set_cubemap_size(new_size);
	}
}

void ScrapEngine::Core::SceneManager::set_light_pos(const SVector3& pos) const
{
	shadowmapping_manager_->set_light_pos(pos.get_glm_vector());
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SceneManager::get_light_pos() const
{
	return SVector3(shadowmapping_manager_->get_light_pos());
}

void ScrapEngine::Core::SceneManager::set_light_lookat(const SVector3& lookat) const
{
	shadowmapping_manager_->set_light_look_at(lookat.get_glm_vector());
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SceneManager::get_light_lookat() const
{
	return SVector3(shadowmapping_manager_->get_light_look_at());
}

float ScrapEngine::Core::SceneManager::get_light_fov() const
{
	return shadowmapping_manager_->get_light_fov();
}

void ScrapEngine::Core::SceneManager::set_light_fov(const float fov) const
{
	shadowmapping_manager_->set_light_fov(fov);
}

float ScrapEngine::Core::SceneManager::get_light_far_distance() const
{
	return shadowmapping_manager_->get_z_far();
}

void ScrapEngine::Core::SceneManager::set_light_far_distance(const float distance) const
{
	shadowmapping_manager_->set_z_far(distance);
}
