#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <map>
#include <Engine/Physics/Manager/PhysicsManager.h>
#include <Engine/LogicCore/Components/ColliderComponent/ColliderComponent.h>
#include <Engine/LogicCore/Components/ColliderComponent/BoxColliderComponent/BoxColliderComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager
		{
		private:
			Render::RenderManager* render_manager_ref_ = nullptr;
			Physics::PhysicsManager* physics_manager_ref_ = nullptr;

			std::map<MeshComponent*, Render::VulkanMeshInstance*> loaded_meshes_;
			std::map<ColliderComponent*, Physics::RigidBody*> loaded_collisions_;
		public:
			explicit ComponentsManager() = default;
			~ComponentsManager() = default;

			void set_render_manager(Render::RenderManager* input_render_manager_ref);
			void set_physics_manager(Physics::PhysicsManager* input_physics_manager);

			//MeshStuff
			MeshComponent* create_new_mesh_component(const std::string& vertex_shader_path,
			                                         const std::string& fragment_shader_path,
			                                         const std::string& model_path,
			                                         const std::vector<std::string>& textures_path);
			void destroy_mesh_component(MeshComponent* component_to_destroy);

			//Physics stuff
			BoxColliderComponent* create_box_collider_component(const Core::SVector3& size,
				const Core::SVector3& start_position,
				float mass = 0.f);

			void destroy_box_collider_component(BoxColliderComponent* component_to_destroy);
		};
	}
}
