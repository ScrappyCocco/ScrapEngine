#pragma once

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
#include <unordered_map>

namespace ScrapEngine
{
	namespace Core
	{
		/**
		 * \brief Struct used to return the raycast result to the user
		 */
		struct raycast_result
		{
			/**
			 * \brief Component hit by the ray or nullptr if none
			 */
			RigidBodyComponent* component_hit = nullptr;
			/**
			 * \brief Hit point in world-space coordinates 
			 */
			SVector3 world_point;
			/**
			 * \brief Surface normal of the proxy shape at the hit point in world-space coordinates 
			 */
			SVector3 world_normal;
			/**
			 * \brief Fraction distance of the hit point between startPoint and endPoint of the ray.
			 * The hit point p is such that p = startPoint + hitFraction ⋅ (endPoint - startPoint)
			 */
			float hit_fraction;
		};

		class ComponentsManager
		{
		private:
			Render::RenderManager* render_manager_ref_ = nullptr;
			Physics::PhysicsManager* physics_manager_ref_ = nullptr;
			Audio::AudioManager* audio_manager_ref_ = nullptr;

			//There is a double-map because this help me searching also by Physics::RigidBody
			//For the raycast i want to get the component from Physics::RigidBody
			std::unordered_map<RigidBodyComponent*, Physics::RigidBody*> loaded_rigidbody_collisions_;
			std::unordered_map<Physics::RigidBody*, RigidBodyComponent*> loaded_rigidbody_inverse_;

			std::unordered_map<MeshComponent*, Render::VulkanMeshInstance*> loaded_meshes_;
			std::unordered_map<TriggerComponent*, Physics::CollisionBody*> loaded_collider_collisions_;

			//Keep a single camera component
			CameraComponent* camera_ = nullptr;
		public:
			explicit ComponentsManager() = default;
			~ComponentsManager() = default;

			void set_render_manager(Render::RenderManager* input_render_manager_ref);
			void set_physics_manager(Physics::PhysicsManager* input_physics_manager);
			void set_audio_manager(Audio::AudioManager* input_audio_manager);

			//----------------------------------------
			//MeshStuff
			//Currently the engine doesn't support custom shaders, so specify the path is kinda useless
			MeshComponent* create_new_mesh_component(const std::string& vertex_shader_path,
			                                         const std::string& fragment_shader_path,
			                                         const std::string& model_path,
			                                         const std::vector<std::string>& textures_path);
			MeshComponent* create_new_mesh_component(const std::string& model_path,
			                                         const std::vector<std::string>& textures_path);
			void destroy_mesh_component(MeshComponent* component_to_destroy);
			//----------------------------------------
			//Camera
			//Remember the camera returned is always the same and unique one
			CameraComponent* get_camera();
			//----------------------------------------
			//Physics stuff
			void update_rigidbody_physics(float factor);
			void destroy_trigger_component(TriggerComponent* component_to_destroy);
			void destroy_rigidbody_component(RigidBodyComponent* component_to_destroy);
			void set_gravity(const SVector3& gravity) const;
			SVector3 get_gravity() const;

			//--->Trigger collisions
			//BoxColliderComponent
			BoxTriggerComponent* create_box_trigger_component(const SVector3& size,
			                                                  const SVector3& start_position);

			//--->Rigidbodies
			//BoxColliderComponent
			BoxRigidBodyComponent* create_box_rigidbody_component(const SVector3& size,
			                                                      const SVector3& start_position,
			                                                      float mass = 0.f);

			//CapsuleColliderComponent
			CapsuleRigidBodyComponent* create_capsule_rigidbody_component(float radius,
			                                                              float height,
			                                                              const SVector3& start_position,
			                                                              float mass = 0.f);
			//SphereColliderComponent
			SphereRigidBodyComponent* create_sphere_rigidbody_component(float radius,
			                                                            const SVector3& start_position,
			                                                            float mass = 0.f);
			//Raycasting
			raycast_result execute_single_raycast(const SVector3& start,
			                                      const SVector3& end);

			std::vector<raycast_result> execute_multi_raycast(const SVector3& start,
			                                                  const SVector3& end);
			//----------------------------------------
			//AudioStuff
			AudioComponent2D* create_2d_sound(const std::string& filename) const;
			AudioComponent3D* create_3d_sound(const std::string& filename) const;
			void unload_sound(AudioComponent* audio) const;
		};
	}
}
