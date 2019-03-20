#pragma once

#include "../../Rendering/Manager/RenderManager.h"
#include "../Components/Manager/ComponentsManager.h"
#include "../Scene/SceneManager.h"
#include "LogicManager.h"

namespace ScrapEngine
{
	namespace Core
	{
		class LogicManagerView
		{
		private:
			ScrapEngine::RenderManager* render_manager_ref_;
			ScrapEngine::Core::LogicManager* logic_manager_ref_;
			ScrapEngine::Core::ComponentsManager* component_manager_;
			ScrapEngine::Core::SceneManager* scene_manager_;
		public:
			LogicManagerView(ScrapEngine::RenderManager* input_render_manager_ref,
			                 ScrapEngine::Core::LogicManager* input_logic_manager_ref);
			~LogicManagerView();

			Core::SGameObject* register_game_object(Core::SGameObject* input_game_object) const;
			void un_register_game_object(Core::SGameObject* input_game_object) const;
			ScrapEngine::Core::ComponentsManager* getComponentsManager() const;
			ScrapEngine::Core::SceneManager* getSceneManager() const;
		};
	}
}
