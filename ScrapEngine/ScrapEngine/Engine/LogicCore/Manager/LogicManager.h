#pragma once
#include <vector>

namespace ScrapEngine
{
	namespace Core
	{
		class SGameObject;

		class LogicManager
		{
		private:
			std::vector<SGameObject*> registered_game_objects_;
		public:
			LogicManager() = default;
			~LogicManager();

			SGameObject* register_game_object(SGameObject* input_game_object);
			void un_register_game_object(SGameObject* input_game_object);
			void delete_game_object(SGameObject* input_game_object);

			//Events
			void execute_game_objects_start_event();
			void execute_game_objects_update_event(float time);
			void execute_game_objects_ongui_event();
		};
	}
}
