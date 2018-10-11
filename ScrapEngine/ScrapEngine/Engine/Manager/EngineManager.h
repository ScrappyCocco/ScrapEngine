#pragma once

#include "../Debug/DebugLog.h"
#include "../Utility/UsefulTypes.h"
#include "../Rendering/Manager/RenderManager.h"
#include "../Rendering/Manager/RenderManagerView.h"
#include "../LogicCore/Manager/LogicManager.h"
#include "../LogicCore/Manager/LogicManagerView.h"

namespace ScrapEngine {
	class EngineManager
	{
	private:
		bool cleanupDone = false;

		ScrapEngine::game_base_info received_base_game_info;

		ScrapEngine::RenderManager* ScrapRenderManager = nullptr;
		ScrapEngine::LogicManager* ScrapLogicManager = nullptr;
	public:
		EngineManager(std::string app_name = "ScrapEngine Game", int app_version = 1, uint32_t window_WIDTH = 800, uint32_t window_HEIGHT = 600, bool fullscreen = false, bool vsync = true);
		~EngineManager();

		void StartGameLoop();

		ScrapEngine::LogicManagerView* LogicManagerView;
		ScrapEngine::RenderManagerView* RenderManagerView;
	private:
		void initializeEngine();

		void initializeRenderManager(const ScrapEngine::game_base_info* game_info);
		void initializeLogicManager();
		void initializeViews();

		void mainGameLoop();

		void cleanupEngine();
	};

}

