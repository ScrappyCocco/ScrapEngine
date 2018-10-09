#include "ComponentsManager.h"

ScrapEngine::ComponentsManager::ComponentsManager(ScrapEngine::RenderManager* input_RenderManagerRef) : RenderManagerRef(input_RenderManagerRef)
{

}

ScrapEngine::MeshComponent* ScrapEngine::ComponentsManager::createNewMeshComponent(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path)
{
	VulkanMeshInstance* mesh = RenderManagerRef->loadMesh(vertex_shader_path, fragment_shader_path, model_path, texture_path);
	ScrapEngine::MeshComponent* meshComponent = new MeshComponent(mesh);
	loadedMeshes.insert(std::pair<ScrapEngine::MeshComponent*, ScrapEngine::VulkanMeshInstance*>(meshComponent, mesh));
	return meshComponent;
}

void ScrapEngine::ComponentsManager::destroyMeshComponent(ScrapEngine::MeshComponent* componentToDestroy)
{
	std::map<ScrapEngine::MeshComponent*, ScrapEngine::VulkanMeshInstance*>::iterator position = loadedMeshes.find(componentToDestroy);
	if (position != loadedMeshes.end()) {
		RenderManagerRef->unloadMesh(position->second);
		loadedMeshes.erase(position);
	}
}
