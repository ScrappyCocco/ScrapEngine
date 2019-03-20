#pragma once

#include "../../Rendering/Manager/RenderManager.h"
#include "../../Rendering/Model/VulkanSkyboxInstance.h"

namespace ScrapEngine
{
	namespace Core
	{
		class SceneManager
		{
		private:
			ScrapEngine::RenderManager* render_manager_ref_;
			ScrapEngine::VulkanSkyboxInstance* current_skybox_;
		public:
			explicit SceneManager(ScrapEngine::RenderManager* input_render_manager_ref);
			~SceneManager() = default;

			void set_skybox(const std::array<std::string, 6>& files_path);
			void set_skybox_size(unsigned int new_size) const;
		};
	}
}
