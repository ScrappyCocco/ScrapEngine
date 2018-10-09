#pragma once

#include "../../Rendering/Manager/RenderManager.h"
#include "../Components/Manager/ComponentsManager.h"
#include "LogicManager.h"

namespace ScrapEngine {

	class LogicManagerView
	{
	private:
		ScrapEngine::RenderManager* RenderManagerRef;
		ScrapEngine::LogicManager* LogicManagerRef;
		ScrapEngine::ComponentsManager* ComponentManager;
	public:
		LogicManagerView(ScrapEngine::RenderManager* input_RenderManagerRef, ScrapEngine::LogicManager* input_LogicManagerRef);
		~LogicManagerView();

		SGameObject* RegisterGameObject(SGameObject* input_GameObject);
		void UnRegisterGameObject(SGameObject* input_GameObject);
		ScrapEngine::ComponentsManager* getComponentsManager() const;
	};

}

