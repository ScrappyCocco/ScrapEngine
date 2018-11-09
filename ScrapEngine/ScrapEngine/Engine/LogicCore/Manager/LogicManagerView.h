#pragma once

#include "../../Rendering/Manager/RenderManager.h"
#include "../Components/Manager/ComponentsManager.h"
#include "../Scene/SceneManager.h"
#include "LogicManager.h"

namespace ScrapEngine {

	class LogicManagerView
	{
	private:
		ScrapEngine::RenderManager* RenderManagerRef;
		ScrapEngine::LogicManager* LogicManagerRef;
		ScrapEngine::ComponentsManager* ComponentManager;
		ScrapEngine::SceneManager* SceneManager;
	public:
		LogicManagerView(ScrapEngine::RenderManager* input_RenderManagerRef, ScrapEngine::LogicManager* input_LogicManagerRef);
		~LogicManagerView();

		SGameObject* RegisterGameObject(SGameObject* input_GameObject);
		void UnRegisterGameObject(SGameObject* input_GameObject);
		ScrapEngine::ComponentsManager* getComponentsManager() const;
		ScrapEngine::SceneManager* getSceneManager() const;
	};

}

