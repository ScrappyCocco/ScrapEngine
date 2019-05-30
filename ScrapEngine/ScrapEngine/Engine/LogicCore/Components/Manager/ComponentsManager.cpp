#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

void ScrapEngine::Core::ComponentsManager::set_render_manager(Render::RenderManager* input_render_manager_ref)
{
	render_manager_ref_ = input_render_manager_ref;
}

void ScrapEngine::Core::ComponentsManager::set_physics_manager(Physics::PhysicsManager* input_physics_manager)
{
	physics_manager_ref_ = input_physics_manager;
}

ScrapEngine::Core::MeshComponent* ScrapEngine::Core::ComponentsManager::create_new_mesh_component(
	const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path,
	const std::vector<std::string>& textures_path)
{
	Render::VulkanMeshInstance* mesh = render_manager_ref_->load_mesh(vertex_shader_path, fragment_shader_path,
	                                                                  model_path,
	                                                                  textures_path);
	MeshComponent* mesh_component = new MeshComponent(mesh);

	std::pair<MeshComponent*, Render::VulkanMeshInstance*> pair_to_insert(mesh_component, mesh);
	loaded_meshes_.insert(pair_to_insert);
	return mesh_component;
}

void ScrapEngine::Core::ComponentsManager::destroy_mesh_component(
	MeshComponent* component_to_destroy)
{
	const std::map<MeshComponent*, Render::VulkanMeshInstance*>::iterator position =
		loaded_meshes_.find(component_to_destroy);
	if (position != loaded_meshes_.end())
	{
		render_manager_ref_->unload_mesh(position->second);
		loaded_meshes_.erase(position);
	}
}

void ScrapEngine::Core::ComponentsManager::update_rigidbody_physics(const float factor)
{
	for(auto const& element : loaded_collisions_)
	{
		element.first->update_transform(factor);
	}
}

ScrapEngine::Core::BoxColliderComponent* ScrapEngine::Core::ComponentsManager::create_box_collider_component(
	const Core::SVector3& size, const Core::SVector3& start_position, float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_box_collider(size, start_position, mass);
	BoxColliderComponent* component = new BoxColliderComponent(body);

	std::pair<ColliderComponent*, Physics::RigidBody*> pair_to_insert(component, body);
	loaded_collisions_.insert(pair_to_insert);

	return component;
}

void ScrapEngine::Core::ComponentsManager::destroy_box_collider_component(BoxColliderComponent* component_to_destroy)
{
	const std::map<ColliderComponent*, Physics::RigidBody*>::iterator position =
		loaded_collisions_.find(component_to_destroy);
	if (position != loaded_collisions_.end())
	{
		physics_manager_ref_->remove_rigidbody(position->second);
		loaded_collisions_.erase(position);
	}
}
