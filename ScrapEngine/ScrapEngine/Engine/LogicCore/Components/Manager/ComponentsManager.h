#pragma once

#include "../../../Rendering/Manager/RenderManager.h"
#include "../MeshComponent/MeshComponent.h"
#include <map>

namespace ScrapEngine {

	class ComponentsManager
	{
	private:
		ScrapEngine::RenderManager* RenderManagerRef;

		std::map<ScrapEngine::MeshComponent*, ScrapEngine::VulkanMeshInstance*> loadedMeshes;
	public:
		ComponentsManager(ScrapEngine::RenderManager* input_RenderManagerRef);
		~ComponentsManager() = default;

		//MeshStuff
		ScrapEngine::MeshComponent* createNewMeshComponent(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path);
		void destroyMeshComponent(ScrapEngine::MeshComponent* componentToDestroy);
	};

}

