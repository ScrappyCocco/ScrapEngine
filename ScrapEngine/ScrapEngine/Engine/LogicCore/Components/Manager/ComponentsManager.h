#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <map>
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

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager
		{
		private:
			Render::RenderManager* render_manager_ref_ = nullptr;
			Physics::PhysicsManager* physics_manager_ref_ = nullptr;
			Audio::AudioManager* audio_manager_ref_ = nullptr;

			std::map<MeshComponent*, Render::VulkanMeshInstance*> loaded_meshes_;
			std::map<RigidBodyComponent*, Physics::RigidBody*> loaded_rigidbody_collisions_;
			std::map<TriggerComponent*, Physics::CollisionBody*> loaded_collider_collisions_;
		public:
			explicit ComponentsManager() = default;
			~ComponentsManager() = default;

			void set_render_manager(Render::RenderManager* input_render_manager_ref);
			void set_physics_manager(Physics::PhysicsManager* input_physics_manager);
			void set_audio_manager(Audio::AudioManager* input_audio_manager);

			//----------------------------------------
			//MeshStuff
			MeshComponent* create_new_mesh_component(const std::string& vertex_shader_path,
			                                         const std::string& fragment_shader_path,
			                                         const std::string& model_path,
			                                         const std::vector<std::string>& textures_path);
			void destroy_mesh_component(MeshComponent* component_to_destroy);

			//----------------------------------------
			//Physics stuff
			void update_rigidbody_physics(float factor);
			void destroy_trigger_component(TriggerComponent* component_to_destroy);
			void destroy_rigidbody_component(RigidBodyComponent* component_to_destroy);

			//--->Trigger collisions
			//BoxColliderComponent
			BoxTriggerComponent* create_box_trigger_component(const Core::SVector3& size,
			                                                    const Core::SVector3& start_position);

			//--->Rigidbodies
			//BoxColliderComponent
			BoxRigidBodyComponent* create_box_rigidbody_component(const Core::SVector3& size,
			                                                      const Core::SVector3& start_position,
			                                                      float mass = 0.f);

			//CapsuleColliderComponent
			CapsuleRigidBodyComponent* create_capsule_rigidbody_component(float radius,
			                                                              float height,
			                                                              const Core::SVector3& start_position,
			                                                              float mass = 0.f);
			//SphereColliderComponent
			SphereRigidBodyComponent* create_sphere_rigidbody_component(float radius,
			                                                            const Core::SVector3& start_position,
			                                                            float mass = 0.f);
			//----------------------------------------
			//AudioStuff
			AudioComponent2D* create_2d_sound(const std::string& filename) const;
			AudioComponent3D* create_3d_sound(const std::string& filename) const;
			void unload_sound(AudioComponent* audio) const;
		};
	}
}
