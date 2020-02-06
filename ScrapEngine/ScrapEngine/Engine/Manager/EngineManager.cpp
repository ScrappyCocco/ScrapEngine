#include <Engine/Manager/EngineManager.h>
#include <chrono>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Input/Gui/GuiInput.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Rendering/Manager/RenderManagerView.h>
#include <Engine/LogicCore/Manager/LogicManager.h>
#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/Audio/Manager/AudioManager.h>
#include <Engine/Physics/Manager/PhysicsManager.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

ScrapEngine::Manager::EngineManager::EngineManager(const std::string& app_name, const int app_version,
                                                   const uint32_t window_width,
                                                   const uint32_t window_height, const bool fullscreen,
                                                   const bool vsync)
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
	//Prepare draw frame
	scrap_render_manager_->prepare_to_draw_frame();
	//Execute game loop until end
	main_game_loop();
	//Execution ended, close the engine
	cleanup_engine();
	Debug::DebugLog::print_to_console_log("---Engine Execution ended---");
}

void ScrapEngine::Manager::EngineManager::initialize_engine()
{
	Debug::DebugLog::print_init_message();
	Debug::DebugLog::print_to_console_log("---initializeEngine()---");
	initialize_render_manager(&received_base_game_info_); //Create the base rendering module
	initialize_logic_manager(); //Create the base logic manager
	initialize_physics_manager(); // Create the physics manager
	initialize_audio_manager(); // Create the audio manager
	initialize_views(); //Create the views for the user
	Debug::DebugLog::print_to_console_log("---initializeEngine() completed---");
}

void ScrapEngine::Manager::EngineManager::initialize_render_manager(const game_base_info* game_info)
{
	scrap_render_manager_ = new Render::RenderManager(game_info);
}

void ScrapEngine::Manager::EngineManager::initialize_logic_manager()
{
	scrap_logic_manager_ = new Core::LogicManager();
	//Reference to update gui input
	scrap_input_manager_ = scrap_render_manager_->get_game_window()->create_window_input_manager();
}

void ScrapEngine::Manager::EngineManager::initialize_physics_manager()
{
	physics_manager_ = new Physics::PhysicsManager();
}

void ScrapEngine::Manager::EngineManager::initialize_audio_manager()
{
	audio_manager_ = new Audio::AudioManager();
}

void ScrapEngine::Manager::EngineManager::initialize_views()
{
	render_manager_view = new Render::RenderManagerView(scrap_render_manager_);
	logic_manager_view = new Core::LogicManagerView(scrap_render_manager_, scrap_logic_manager_);
	//Set managers to logic core
	logic_manager_view->set_physics_manager(physics_manager_);
	logic_manager_view->set_audio_manager(audio_manager_);
}

void ScrapEngine::Manager::EngineManager::main_game_loop()
{
	Debug::DebugLog::print_to_console_log("---mainGameLoop() started---");
	std::chrono::time_point<std::chrono::steady_clock> start_time, current_time;
	const Render::GameWindow* window_ref = scrap_render_manager_->get_game_window();
	while (!window_ref->check_window_should_close())
	{
		//Compute frame delta time
		const float time = std::chrono::duration<float, std::chrono::seconds::period>
			(current_time - start_time).count();
		//Execute objects update()
		scrap_logic_manager_->execute_game_objects_update_event(time);
		//Gui data update
		gui_update(time);
		//Update physics
		physics_update(time);
		//Update audio
		audio_update();
		//Draw frame and compute new times
		start_time = std::chrono::high_resolution_clock::now();
		scrap_render_manager_->draw_frame();
		current_time = std::chrono::high_resolution_clock::now();
	}
	scrap_render_manager_->wait_device_idle();
	Debug::DebugLog::print_to_console_log("---mainGameLoop() ended---");
}

void ScrapEngine::Manager::EngineManager::physics_update(const float delta_time)
{
	accumulator_ += delta_time;
	while (accumulator_ >= time_step_)
	{
		physics_manager_->update_physics(time_step_);
		accumulator_ -= time_step_;
	}
	const float factor = accumulator_ / time_step_;
	//Once physics ended updating, update the rigidbody component position
	logic_manager_view->get_components_manager()->update_rigidbody_physics(factor);
}

void ScrapEngine::Manager::EngineManager::gui_update(const float time) const
{
	//Mouse location
	const Input::mouse_location loc = scrap_input_manager_->get_last_mouse_location();

	Input::GuiInput::update_mouse_location(loc.xpos, loc.ypos);

	//Mouse click
	Input::GuiInput::update_mouse_click(
		scrap_input_manager_->get_mouse_button_pressed(0),
		scrap_input_manager_->get_mouse_button_pressed(1)
	);

	//Delta time
	if (time > 0)
	{
		Input::GuiInput::update_delta_time(time);
	}

	//Run gui render update
	scrap_render_manager_->pre_gui_render();
	scrap_logic_manager_->execute_game_objects_ongui_event();
	scrap_render_manager_->post_gui_render();
}

void ScrapEngine::Manager::EngineManager::audio_update() const
{
	audio_manager_->audio_update(scrap_render_manager_->get_render_camera());
}

void ScrapEngine::Manager::EngineManager::cleanup_engine()
{
	Debug::DebugLog::print_to_console_log("---cleanupEngine()---");

	delete scrap_render_manager_;
	delete render_manager_view;
	delete logic_manager_view;
	delete physics_manager_;
	delete audio_manager_;
	delete scrap_logic_manager_;

	cleanup_done_ = true;
	Debug::DebugLog::print_to_console_log("---cleanupEngine() completed---");
}
