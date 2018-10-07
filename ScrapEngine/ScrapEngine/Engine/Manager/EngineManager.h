#pragma once

#include "../Debug/DebugLog.h"
#include "UsefulTypes.h"
#include "../Rendering/Manager/RenderManager.h"
#include "../LogicCore/Manager/LogicManager.h"

namespace ScrapEngine {
	class EngineManager
	{
	private:
		bool cleanupDone = false;

		ScrapEngine::RenderManager* ScrapRenderManager = nullptr;
		ScrapEngine::LogicManager* ScrapLogicManager = nullptr;
	public:
		EngineManager(std::string app_name = "ScrapEngine Game", int app_version = 1, uint32_t window_WIDTH = 800, uint32_t window_HEIGHT = 600, bool fullscreen = false);
		~EngineManager();

		void StartGameLoop();

		const ScrapEngine::GameWindow* getGameWindow() const;
	private:
		ScrapEngine::game_base_info received_base_game_info;

		void initializeEngine();

		void initializeRenderManager(const ScrapEngine::game_base_info* game_info);
		void initializeLogicManager();

		void mainGameLoop();

		void cleanupEngine();
	};

}

