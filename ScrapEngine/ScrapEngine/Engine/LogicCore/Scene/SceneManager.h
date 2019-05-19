#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Rendering/Model/VulkanSkyboxInstance.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SceneManager
		{
		private:
			ScrapEngine::Render::RenderManager* render_manager_ref_;
			ScrapEngine::Render::VulkanSkyboxInstance* current_skybox_;
		public:
			explicit SceneManager(ScrapEngine::Render::RenderManager* input_render_manager_ref);
			~SceneManager() = default;

			void set_skybox(const std::array<std::string, 6>& files_path);
			void set_skybox_size(unsigned int new_size) const;
		};
	}
}
