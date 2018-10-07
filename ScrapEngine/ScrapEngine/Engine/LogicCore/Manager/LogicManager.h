#pragma once

#include "../Components/SComponent.h"
#include "../GameObject/SGameObject.h"

namespace ScrapEngine {

	class LogicManager
	{
	private:
		std::vector<SGameObject*> RegisteredGameObjects;
	public:
		LogicManager();
		~LogicManager();

		SGameObject* RegisterGameObject(SGameObject* input_GameObject);
		void UnRegisterGameObject(SGameObject* input_GameObject);
		void ExecuteGameObjectsStartEvent();
		void ExecuteGameObjectsUpdateEvent();
	};

}

