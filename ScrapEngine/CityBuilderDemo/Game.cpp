#include <iostream>
#include <Engine/Manager/EngineManager.h>
#include <Engine/Input/Manager/InputManager.h>

int main()
{
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::Manager::EngineManager* scrap_engine_manager = nullptr;
	try
	{
		//Init engine
		scrap_engine_manager = new ScrapEngine::Manager::EngineManager("Example Game", 0, 1280, 720);
		ScrapEngine::Render::GameWindow* game_window_ref = scrap_engine_manager->render_manager_view->get_game_window();
		//Create the input manager
		ScrapEngine::Input::InputManager* inputmanager = game_window_ref->create_window_input_manager();
		//Get the component manager
		ScrapEngine::Core::ComponentsManager* component_manager_ref = scrap_engine_manager
		                                                              ->logic_manager_view->get_components_manager();
		//Set the world skybox
		ScrapEngine::Core::SceneManager* scene_manager_ref = scrap_engine_manager
		                                                     ->logic_manager_view->get_scene_manager();
		scene_manager_ref->set_skybox(
			std::array<std::string, 6>{
				"../assets/skybox/stormydays_ft.png", //FRONT TEXTURE
				"../assets/skybox/stormydays_bk.png", //BACK TEXTURE
				"../assets/skybox/stormydays_up.png", //UP TEXTURE
				"../assets/skybox/stormydays_dn.png", //DOWN TEXTURE
				"../assets/skybox/stormydays_rt.png", //RIGHT TEXTURE
				"../assets/skybox/stormydays_lf.png", //LEFT TEXTURE
			}
		);
		scene_manager_ref->set_skybox_size(500);
		//Create the camera
		/*GameCamera* game_camera_ref = new GameCamera(inputmanager,
		                                             scrap_engine_manager
		                                             ->render_manager_view->get_default_render_camera(),
		                                             ball_game_object);
		game_camera_ref->set_game_window_ref(game_window_ref);
		scrap_engine_manager->logic_manager_view->register_game_object(game_camera_ref);*/
		//Begin gameplay
		scrap_engine_manager->start_game_loop();
		//End gameplay
	}
	catch (const std::exception& e)
	{
		std::cerr << "EXCEPTION MESSAGE-->" << e.what() << std::endl;
		exit_value = EXIT_FAILURE;
	}
	//Delete
	delete scrap_engine_manager;
	//Display error message
	if (exit_value == EXIT_FAILURE)
	{
		//Exit failure, whait to close
		std::cout << std::endl << "EXIT_FAILURE - Press to exit..." << std::endl;
		fflush(stdin);
		getchar();
	}
	else
	{
		std::cout << std::endl << "EXIT_SUCCESS" << std::endl;
	}
	//End of program
	return exit_value;
}
