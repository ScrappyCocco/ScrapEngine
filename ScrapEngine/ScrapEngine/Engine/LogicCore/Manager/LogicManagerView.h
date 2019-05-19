#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/LogicCore/Scene/SceneManager.h>
#include <Engine/LogicCore/Manager/LogicManager.h>

namespace ScrapEngine
{
	namespace Core
	{
		class LogicManagerView
		{
		private:
			ScrapEngine::Core::LogicManager* logic_manager_ref_;
			ScrapEngine::Core::ComponentsManager* component_manager_;
			ScrapEngine::Core::SceneManager* scene_manager_;
		public:
			LogicManagerView(ScrapEngine::Render::RenderManager* input_render_manager_ref,
			                 ScrapEngine::Core::LogicManager* input_logic_manager_ref);
			~LogicManagerView();

			Core::SGameObject* register_game_object(Core::SGameObject* input_game_object) const;
			void un_register_game_object(Core::SGameObject* input_game_object) const;
			ScrapEngine::Core::ComponentsManager* get_components_manager() const;
			ScrapEngine::Core::SceneManager* get_scene_manager() const;
		};
	}
}
