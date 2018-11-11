#include "EngineManager.h"
#include <chrono>

ScrapEngine::EngineManager::EngineManager(std::string app_name, int app_version, uint32_t window_WIDTH, uint32_t window_HEIGHT, bool fullscreen, bool vsync)
	: received_base_game_info(app_name, app_version, window_WIDTH, window_HEIGHT, fullscreen, vsync)
{
	initializeEngine();
}

ScrapEngine::EngineManager::~EngineManager()
{
	if (!cleanupDone) { //Check if the cleanup has already been done
		cleanupEngine();
	}
}

void ScrapEngine::EngineManager::StartGameLoop()
{
	//Execute Game Objects start events
	ScrapLogicManager->ExecuteGameObjectsStartEvent();
	//Execute game loop until end
	mainGameLoop();
	//Execution ended, close the engine
	cleanupEngine();
	DebugLog::printToConsoleLog("---Engine Execution ended---");
}

void ScrapEngine::EngineManager::initializeEngine()
{
	DebugLog::printToConsoleLog("---initializeEngine()---");
	initializeRenderManager(&received_base_game_info); //Create the base rendering module
	initializeLogicManager(); //Create the base logic manager
	initializeViews(); //Create the views for the user
	DebugLog::printToConsoleLog("---initializeEngine() completed---");
}

void ScrapEngine::EngineManager::initializeRenderManager(const ScrapEngine::game_base_info* game_info)
{
	ScrapRenderManager = new RenderManager(game_info);
}

void ScrapEngine::EngineManager::initializeLogicManager()
{
	ScrapLogicManager = new LogicManager();
}

void ScrapEngine::EngineManager::initializeViews()
{
	RenderManagerView = new ScrapEngine::RenderManagerView(ScrapRenderManager);
	LogicManagerView = new ScrapEngine::LogicManagerView(ScrapRenderManager, ScrapLogicManager);
}

void ScrapEngine::EngineManager::mainGameLoop()
{
	DebugLog::printToConsoleLog("---mainGameLoop() started---");
	std::chrono::time_point<std::chrono::steady_clock> startTime, currentTime;
	float time;
	const ScrapEngine::GameWindow* window_ref = ScrapRenderManager->getGameWindow();
	while (!window_ref->checkWindowShouldClose()) {
		time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		ScrapLogicManager->ExecuteGameObjectsUpdateEvent(time);
		startTime = std::chrono::high_resolution_clock::now();
		ScrapRenderManager->drawFrame();
		currentTime = std::chrono::high_resolution_clock::now();
	}
	ScrapRenderManager->waitDeviceIdle();
	DebugLog::printToConsoleLog("---mainGameLoop() ended---");
}

void ScrapEngine::EngineManager::cleanupEngine()
{
	DebugLog::printToConsoleLog("---cleanupEngine()---");
	
	delete ScrapRenderManager;
	delete RenderManagerView;
	delete LogicManagerView;
	delete ScrapLogicManager;
	
	cleanupDone = true;
	DebugLog::printToConsoleLog("---cleanupEngine() completed---");
}
