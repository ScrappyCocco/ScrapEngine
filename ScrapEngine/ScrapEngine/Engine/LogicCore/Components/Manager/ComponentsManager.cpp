#include "ComponentsManager.h"

ScrapEngine::Core::ComponentsManager::ComponentsManager(ScrapEngine::Render::RenderManager* input_render_manager_ref) : render_manager_ref_(input_render_manager_ref)
{
}

ScrapEngine::Core::MeshComponent* ScrapEngine::Core::ComponentsManager::create_new_mesh_component(
	const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path,
	const std::string& texture_path)
{
	Render::VulkanMeshInstance* mesh = render_manager_ref_->loadMesh(vertex_shader_path, fragment_shader_path, model_path,
	                                                         texture_path);
	ScrapEngine::Core::MeshComponent* mesh_component = new MeshComponent(mesh);
	loaded_meshes_.insert(
		std::pair<ScrapEngine::Core::MeshComponent*, ScrapEngine::Render::VulkanMeshInstance*>(mesh_component, mesh));
	return mesh_component;
}

void ScrapEngine::Core::ComponentsManager::destroy_mesh_component(
	ScrapEngine::Core::MeshComponent* component_to_destroy)
{
	const std::map<ScrapEngine::Core::MeshComponent*, ScrapEngine::Render::VulkanMeshInstance*>::iterator position =
		loaded_meshes_.
		find(component_to_destroy);
	if (position != loaded_meshes_.end())
	{
		render_manager_ref_->unloadMesh(position->second);
		loaded_meshes_.erase(position);
	}
}
