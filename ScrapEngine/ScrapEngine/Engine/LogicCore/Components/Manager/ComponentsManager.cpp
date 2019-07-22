#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

void ScrapEngine::Core::ComponentsManager::set_render_manager(Render::RenderManager* input_render_manager_ref)
{
	render_manager_ref_ = input_render_manager_ref;
}

void ScrapEngine::Core::ComponentsManager::set_physics_manager(Physics::PhysicsManager* input_physics_manager)
{
	physics_manager_ref_ = input_physics_manager;
}

void ScrapEngine::Core::ComponentsManager::set_audio_manager(Audio::AudioManager* input_audio_manager)
{
	audio_manager_ref_ = input_audio_manager;
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
	for (auto const& element : loaded_rigidbody_collisions_)
	{
		element.first->update_transform(factor);
	}
}

ScrapEngine::Core::BoxRigidBodyComponent* ScrapEngine::Core::ComponentsManager::create_box_rigidbody_component(
	const Core::SVector3& size, const Core::SVector3& start_position, const float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_box_rigidbody(size, start_position, mass);
	BoxRigidBodyComponent* component = new BoxRigidBodyComponent(body);

	std::pair<RigidBodyComponent*, Physics::RigidBody*> pair_to_insert(component, body);
	loaded_rigidbody_collisions_.insert(pair_to_insert);

	return component;
}

ScrapEngine::Core::CapsuleRigidBodyComponent* ScrapEngine::Core::ComponentsManager::create_capsule_rigidbody_component(
	const float radius, const float height, const Core::SVector3& start_position, const float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_capsule_rigidbody(radius, height, start_position, mass);
	CapsuleRigidBodyComponent* component = new CapsuleRigidBodyComponent(body);

	std::pair<RigidBodyComponent*, Physics::RigidBody*> pair_to_insert(component, body);
	loaded_rigidbody_collisions_.insert(pair_to_insert);

	return component;
}

ScrapEngine::Core::SphereRigidBodyComponent* ScrapEngine::Core::ComponentsManager::create_sphere_rigidbody_component(
	const float radius, const Core::SVector3& start_position, const float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_sphere_rigidbody(radius, start_position, mass);
	SphereRigidBodyComponent* component = new SphereRigidBodyComponent(body);

	std::pair<RigidBodyComponent*, Physics::RigidBody*> pair_to_insert(component, body);
	loaded_rigidbody_collisions_.insert(pair_to_insert);

	return component;
}

ScrapEngine::Core::AudioComponent2D* ScrapEngine::Core::ComponentsManager::create_2d_sound(const std::string& filename) const
{
	return new AudioComponent2D(audio_manager_ref_->load_2d_sound(filename));
}

ScrapEngine::Core::AudioComponent3D* ScrapEngine::Core::ComponentsManager::create_3d_sound(const std::string& filename) const
{
	return new AudioComponent3D(audio_manager_ref_->load_3d_sound(filename));
}

void ScrapEngine::Core::ComponentsManager::destroy_rigidbody_component(RigidBodyComponent* component_to_destroy)
{
	const std::map<RigidBodyComponent*, Physics::RigidBody*>::iterator position =
		loaded_rigidbody_collisions_.find(component_to_destroy);
	if (position != loaded_rigidbody_collisions_.end())
	{
		physics_manager_ref_->remove_rigidbody(position->second);
		loaded_rigidbody_collisions_.erase(position);
	}
}

ScrapEngine::Core::BoxTriggerComponent* ScrapEngine::Core::ComponentsManager::create_box_trigger_component(
	const Core::SVector3& size, const Core::SVector3& start_position)
{
	Physics::CollisionBody* body = physics_manager_ref_->create_box_trigger(size, start_position);
	BoxTriggerComponent* component = new BoxTriggerComponent(body);

	std::pair<TriggerComponent*, Physics::CollisionBody*> pair_to_insert(component, body);
	loaded_collider_collisions_.insert(pair_to_insert);

	return component;
}

void ScrapEngine::Core::ComponentsManager::destroy_trigger_component(TriggerComponent* component_to_destroy)
{
	const std::map<TriggerComponent*, Physics::CollisionBody*>::iterator position =
		loaded_collider_collisions_.find(component_to_destroy);
	if (position != loaded_collider_collisions_.end())
	{
		physics_manager_ref_->remove_collider(position->second);
		loaded_collider_collisions_.erase(position);
	}
}
