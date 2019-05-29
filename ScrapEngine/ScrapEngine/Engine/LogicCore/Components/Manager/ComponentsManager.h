#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <map>

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager
		{
		private:
			Render::RenderManager* render_manager_ref_;

			std::map<MeshComponent*, Render::VulkanMeshInstance*> loaded_meshes_;
		public:
			explicit ComponentsManager(Render::RenderManager* input_render_manager_ref);
			~ComponentsManager() = default;

			//MeshStuff
			MeshComponent* create_new_mesh_component(const std::string& vertex_shader_path,
			                                         const std::string& fragment_shader_path,
			                                         const std::string& model_path,
			                                         const std::vector<std::string>& textures_path);
			void destroy_mesh_component(MeshComponent* component_to_destroy);
		};
	}
}
