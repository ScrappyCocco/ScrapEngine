#pragma once

#include "../../Rendering/Manager/RenderManager.h"
#include "../../Rendering/Model/VulkanSkyboxInstance.h"

namespace ScrapEngine {
	class SceneManager
	{
	private:
		ScrapEngine::RenderManager* RenderManagerRef;
		ScrapEngine::VulkanSkyboxInstance* CurrentSkybox;
	public:
		SceneManager(ScrapEngine::RenderManager* input_RenderManagerRef);
		~SceneManager();

		void setSkybox(const std::array<std::string, 6>& files_path);
		void setSkyboxSize(unsigned int newSize);
	};
}

