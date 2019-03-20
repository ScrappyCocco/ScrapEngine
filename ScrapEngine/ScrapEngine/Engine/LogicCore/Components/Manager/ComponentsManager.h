#pragma once

#include "../../../Rendering/Manager/RenderManager.h"
#include "../MeshComponent/MeshComponent.h"
#include <map>

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager
		{
		private:
			ScrapEngine::RenderManager* render_manager_ref_;

			std::map<ScrapEngine::Core::MeshComponent*, ScrapEngine::VulkanMeshInstance*> loaded_meshes_;
		public:
			explicit ComponentsManager(ScrapEngine::RenderManager* input_render_manager_ref);
			~ComponentsManager() = default;

			//MeshStuff
			ScrapEngine::Core::MeshComponent* create_new_mesh_component(const std::string& vertex_shader_path,
			                                                            const std::string& fragment_shader_path,
			                                                            const std::string& model_path,
			                                                            const std::string& texture_path);
			void destroy_mesh_component(ScrapEngine::Core::MeshComponent* component_to_destroy);
		};
	}
}
