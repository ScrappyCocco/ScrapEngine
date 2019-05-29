#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SceneManager
		{
		private:
			Render::RenderManager* render_manager_ref_;
			Render::VulkanSkyboxInstance* current_skybox_;
		public:
			explicit SceneManager(Render::RenderManager* input_render_manager_ref);
			~SceneManager() = default;

			void set_skybox(const std::array<std::string, 6>& files_path);
			void set_skybox_size(unsigned int new_size) const;
		};
	}
}
