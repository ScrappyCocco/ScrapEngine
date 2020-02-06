#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/Physics/Manager/PhysicsManager.h>
#include <Engine/LogicCore/Components/TriggerComponent/TriggerComponent.h>
#include <Engine/LogicCore/Components/TriggerComponent/BoxTriggerComponent/BoxTriggerComponent.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/BoxRigidBodyComponent/BoxRigidBodyComponent.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/CapsuleRigidBodyComponent/CapsuleRigidBodyComponent.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/SphereRigidBodyComponent/SphereRigidBodyComponent.h>
#include <Engine/Audio/Manager/AudioManager.h>
#include <Engine/LogicCore/Components/AudioComponent/2dAudioComponent/2DAudioComponent.h>
#include <Engine/LogicCore/Components/AudioComponent/3dAudioComponent/3DAudioComponent.h>
#include <Engine/LogicCore/Components/CameraComponent/CameraComponent.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>

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

	loaded_meshes_.insert({mesh_component, mesh});

	return mesh_component;
}

ScrapEngine::Core::MeshComponent* ScrapEngine::Core::ComponentsManager::create_new_mesh_component(
	const std::string& model_path, const std::vector<std::string>& textures_path)
{
	//Use default render_manager_ shader
	Render::VulkanMeshInstance* mesh = render_manager_ref_->load_mesh(
		model_path,
		textures_path);
	MeshComponent* mesh_component = new MeshComponent(mesh);

	loaded_meshes_.insert({mesh_component, mesh});

	return mesh_component;
}

void ScrapEngine::Core::ComponentsManager::destroy_mesh_component(
	MeshComponent* component_to_destroy)
{
	//If the element is present
	if (loaded_meshes_.find(component_to_destroy) != loaded_meshes_.end())
	{
		loaded_meshes_[component_to_destroy]->set_for_deletion();
		//Erase by key
		loaded_meshes_.erase(component_to_destroy);
	}
}

ScrapEngine::Core::CameraComponent* ScrapEngine::Core::ComponentsManager::get_camera()
{
	if (!camera_)
	{
		camera_ = new CameraComponent(render_manager_ref_->get_default_render_camera());
	}
	return camera_;
}

void ScrapEngine::Core::ComponentsManager::update_rigidbody_physics(const float factor)
{
	for (auto const& element : loaded_rigidbody_collisions_)
	{
		element.first->update_transform(factor);
	}
}

ScrapEngine::Core::BoxRigidBodyComponent* ScrapEngine::Core::ComponentsManager::create_box_rigidbody_component(
	const SVector3& size, const SVector3& start_position, const float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_box_rigidbody(size, start_position, mass);
	BoxRigidBodyComponent* component = new BoxRigidBodyComponent(body);

	loaded_rigidbody_collisions_.insert({component, body});
	loaded_rigidbody_inverse_.insert({body, component});

	return component;
}

ScrapEngine::Core::CapsuleRigidBodyComponent* ScrapEngine::Core::ComponentsManager::create_capsule_rigidbody_component(
	const float radius, const float height, const SVector3& start_position, const float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_capsule_rigidbody(radius, height, start_position, mass);
	CapsuleRigidBodyComponent* component = new CapsuleRigidBodyComponent(body);

	loaded_rigidbody_collisions_.insert({component, body});
	loaded_rigidbody_inverse_.insert({body, component});

	return component;
}

ScrapEngine::Core::SphereRigidBodyComponent* ScrapEngine::Core::ComponentsManager::create_sphere_rigidbody_component(
	const float radius, const SVector3& start_position, const float mass)
{
	Physics::RigidBody* body = physics_manager_ref_->create_sphere_rigidbody(radius, start_position, mass);
	SphereRigidBodyComponent* component = new SphereRigidBodyComponent(body);

	loaded_rigidbody_collisions_.insert({component, body});
	loaded_rigidbody_inverse_.insert({body, component});

	return component;
}

ScrapEngine::Core::raycast_result ScrapEngine::Core::ComponentsManager::execute_single_raycast(
	const SVector3& start, const SVector3& end)
{
	const Physics::RaycastResultInfo result = physics_manager_ref_->execute_single_raycast(start, end);
	raycast_result return_info{};

	if (result.body)
	{
		return_info.world_point = result.world_point;
		return_info.world_normal = result.world_normal;
		return_info.hit_fraction = result.hit_fraction;
		return_info.component_hit = loaded_rigidbody_inverse_[result.body];
	}

	return return_info;
}

std::vector<ScrapEngine::Core::raycast_result> ScrapEngine::Core::ComponentsManager::execute_multi_raycast(
	const SVector3& start, const SVector3& end)
{
	const std::vector<Physics::RaycastResultInfo> result = physics_manager_ref_->execute_multi_raycast(start, end);
	std::vector<ScrapEngine::Core::raycast_result> return_info;

	if (result.size() > 0)
	{
		for (auto element : result)
		{
			//double-check that element exist
			if (element.body)
			{
				//set element info
				raycast_result element_info{};
				element_info.world_point = element.world_point;
				element_info.world_normal = element.world_normal;
				element_info.hit_fraction = element.hit_fraction;
				element_info.component_hit = loaded_rigidbody_inverse_[element.body];
				//Add it to results
				return_info.push_back(element_info);
			}
		}
	}

	return return_info;
}

ScrapEngine::Core::AudioComponent2D* ScrapEngine::Core::ComponentsManager::create_2d_sound(
	const std::string& filename) const
{
	return new AudioComponent2D(audio_manager_ref_->load_2d_sound(filename));
}

ScrapEngine::Core::AudioComponent3D* ScrapEngine::Core::ComponentsManager::create_3d_sound(
	const std::string& filename) const
{
	return new AudioComponent3D(audio_manager_ref_->load_3d_sound(filename));
}

void ScrapEngine::Core::ComponentsManager::unload_sound(AudioComponent* audio) const
{
	audio_manager_ref_->unload_sound(audio->get_raw_source());
}

void ScrapEngine::Core::ComponentsManager::destroy_rigidbody_component(RigidBodyComponent* component_to_destroy)
{
	//If the element is present
	if (loaded_rigidbody_collisions_.find(component_to_destroy) != loaded_rigidbody_collisions_.end())
	{
		//Erase in the first map
		loaded_rigidbody_inverse_.erase(loaded_rigidbody_collisions_[component_to_destroy]);
		//Remove it
		physics_manager_ref_->remove_rigidbody(loaded_rigidbody_collisions_[component_to_destroy]);
		//Erase by key
		loaded_rigidbody_collisions_.erase(component_to_destroy);
	}
}

void ScrapEngine::Core::ComponentsManager::set_gravity(const SVector3& gravity) const
{
	physics_manager_ref_->set_gravity(gravity);
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::ComponentsManager::get_gravity() const
{
	return physics_manager_ref_->get_gravity();
}

ScrapEngine::Core::BoxTriggerComponent* ScrapEngine::Core::ComponentsManager::create_box_trigger_component(
	const SVector3& size, const SVector3& start_position)
{
	Physics::CollisionBody* body = physics_manager_ref_->create_box_trigger(size, start_position);
	BoxTriggerComponent* component = new BoxTriggerComponent(body);

	loaded_collider_collisions_.insert({component, body});

	return component;
}

void ScrapEngine::Core::ComponentsManager::destroy_trigger_component(TriggerComponent* component_to_destroy)
{
	//If the element is present
	if (loaded_collider_collisions_.find(component_to_destroy) != loaded_collider_collisions_.end())
	{
		physics_manager_ref_->remove_collider(loaded_collider_collisions_[component_to_destroy]);
		//Erase by key
		loaded_collider_collisions_.erase(component_to_destroy);
	}
}
