#include <Engine/LogicCore/Manager/LogicManager.h>

ScrapEngine::Core::LogicManager::~LogicManager()
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		delete game_object;
	}
}

ScrapEngine::Core::SGameObject* ScrapEngine::Core::LogicManager::register_game_object(
	SGameObject* input_game_object)
{
	registered_game_objects_.push_back(input_game_object);
	return registered_game_objects_.back();
}

void ScrapEngine::Core::LogicManager::un_register_game_object(SGameObject* input_game_object)
{
	const std::vector<SGameObject*>::iterator element = find(registered_game_objects_.begin(),
	                                                         registered_game_objects_.end(),
	                                                         input_game_object);
	if (element != registered_game_objects_.end())
	{
		delete *element;
		registered_game_objects_.erase(element);
	}
}

void ScrapEngine::Core::LogicManager::execute_game_objects_start_event()
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		game_object->game_start();
	}
}

void ScrapEngine::Core::LogicManager::execute_game_objects_update_event(const float time)
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		if (game_object->get_should_update()) {
			game_object->game_update(time);
		}
	}
}

void ScrapEngine::Core::LogicManager::execute_game_objects_ongui_event()
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		if (game_object->get_should_update()) {
			game_object->on_gui();
		}
	}
}
