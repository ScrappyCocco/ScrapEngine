#include "EngineManager.h"
#include <chrono>
#include "Engine/Debug/DebugLog.h"

ScrapEngine::Manager::EngineManager::EngineManager(std::string app_name, int app_version, uint32_t window_width,
                                                   uint32_t window_height, bool fullscreen, bool vsync)
	: received_base_game_info_(app_name, app_version, window_width, window_height, fullscreen, vsync)
{
	initialize_engine();
}

ScrapEngine::Manager::EngineManager::~EngineManager()
{
	if (!cleanup_done_)
	{
		//Check if the cleanup has already been done
		cleanup_engine();
	}
}

void ScrapEngine::Manager::EngineManager::start_game_loop()
{
	//Execute Game Objects start events
	scrap_logic_manager_->execute_game_objects_start_event();
	//Execute game loop until end
	main_game_loop();
	//Execution ended, close the engine
	cleanup_engine();
	Debug::DebugLog::print_to_console_log("---Engine Execution ended---");
}

void ScrapEngine::Manager::EngineManager::initialize_engine()
{
	Debug::DebugLog::print_to_console_log("---initializeEngine()---");
	initialize_render_manager(&received_base_game_info_); //Create the base rendering module
	initialize_logic_manager(); //Create the base logic manager
	initialize_views(); //Create the views for the user
	Debug::DebugLog::print_to_console_log("---initializeEngine() completed---");
}

void ScrapEngine::Manager::EngineManager::initialize_render_manager(const ScrapEngine::game_base_info* game_info)
{
	scrap_render_manager_ = new Render::RenderManager(game_info);
}

void ScrapEngine::Manager::EngineManager::initialize_logic_manager()
{
	scrap_logic_manager_ = new Core::LogicManager();
}

void ScrapEngine::Manager::EngineManager::initialize_views()
{
	render_manager_view = new ScrapEngine::Render::RenderManagerView(scrap_render_manager_);
	logic_manager_view = new ScrapEngine::Core::LogicManagerView(scrap_render_manager_, scrap_logic_manager_);
}

void ScrapEngine::Manager::EngineManager::main_game_loop() const
{
	Debug::DebugLog::print_to_console_log("---mainGameLoop() started---");
	std::chrono::time_point<std::chrono::steady_clock> startTime, currentTime;
	const ScrapEngine::Render::GameWindow* window_ref = scrap_render_manager_->get_game_window();
	while (!window_ref->check_window_should_close())
	{
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		scrap_logic_manager_->execute_game_objects_update_event(time);
		startTime = std::chrono::high_resolution_clock::now();
		scrap_render_manager_->draw_frame();
		currentTime = std::chrono::high_resolution_clock::now();
	}
	scrap_render_manager_->wait_device_idle();
	Debug::DebugLog::print_to_console_log("---mainGameLoop() ended---");
}

void ScrapEngine::Manager::EngineManager::cleanup_engine()
{
	Debug::DebugLog::print_to_console_log("---cleanupEngine()---");

	delete scrap_render_manager_;
	delete render_manager_view;
	delete logic_manager_view;
	delete scrap_logic_manager_;

	cleanup_done_ = true;
	Debug::DebugLog::print_to_console_log("---cleanupEngine() completed---");
}
