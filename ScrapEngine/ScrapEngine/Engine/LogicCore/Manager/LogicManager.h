#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace ScrapEngine
{
	namespace Core
	{
		class LogicManager
		{
		private:
			std::vector<SGameObject*> registered_game_objects_;
		public:
			LogicManager() = default;
			~LogicManager();

			SGameObject* register_game_object(SGameObject* input_game_object);
			void un_register_game_object(SGameObject* input_game_object);
			void execute_game_objects_start_event();
			void execute_game_objects_update_event(float time);
		};
	}
}
