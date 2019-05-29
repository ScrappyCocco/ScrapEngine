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
			LogicManager* logic_manager_ref_;
			ComponentsManager* component_manager_;
			SceneManager* scene_manager_;
		public:
			LogicManagerView(Render::RenderManager* input_render_manager_ref,
			                 LogicManager* input_logic_manager_ref);
			~LogicManagerView();

			SGameObject* register_game_object(SGameObject* input_game_object) const;
			void un_register_game_object(SGameObject* input_game_object) const;
			ComponentsManager* get_components_manager() const;
			SceneManager* get_scene_manager() const;
		};
	}
}
