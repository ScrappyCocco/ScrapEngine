#pragma once

#include "../Components/SComponent.h"
#include "../GameObject/SGameObject.h"

namespace ScrapEngine
{
	namespace Core
	{
		class LogicManager
		{
		private:
			std::vector<Core::SGameObject*> registered_game_objects_;
		public:
			LogicManager();
			~LogicManager();

			Core::SGameObject* register_game_object(Core::SGameObject* input_game_object);
			void un_register_game_object(Core::SGameObject* input_game_object);
			void execute_game_objects_start_event();
			void execute_game_objects_update_event(float time);
		};
	}
}
