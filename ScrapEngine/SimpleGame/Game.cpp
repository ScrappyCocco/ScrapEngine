#include <iostream>
#include <Engine/Manager/EngineManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include "GameObjects/Camera/GameCamera.h"
#include "GameObjects/Player/Ball.h"
#include "GameObjects/RespawnTrigger/Trigger.h"
#include "GameObjects/Music/Music.h"
#include "GameObjects/WorldTerrain/WorldTerrainCreator.h"
#include "GameObjects/WorldObjects/WorldObjectsCreator.h"

int main()
{
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::Manager::EngineManager* ScrapEngineManager = nullptr;
	try
	{
		//Init engine
		ScrapEngineManager = new ScrapEngine::Manager::EngineManager("Example Game", 0, 1280, 720);
		ScrapEngine::Render::GameWindow* gameWindowRef = ScrapEngineManager->render_manager_view->get_game_window();
		gameWindowRef->set_window_icon("../assets/game_icon/crate_icon.png");
		//Create the input manager
		ScrapEngine::Input::InputManager* inputmanager = gameWindowRef->create_window_input_manager();
		//inputmanager->set_cursor_input_mode(ScrapEngine::Input::cursor_mode::cursor_grabbed_mode);
		//Get the component manager
		ScrapEngine::Core::ComponentsManager* component_manager_ref = ScrapEngineManager
		                                                            ->logic_manager_view->get_components_manager();
		//Set the world skybox
		ScrapEngine::Core::SceneManager* scene_manager_ref = ScrapEngineManager->logic_manager_view->get_scene_manager();
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
		//Set world gravity
		component_manager_ref->set_gravity(ScrapEngine::Core::SVector3(0, -50, 0));
		//Create the first game object
		//Ball - Player
		Ball* ball_game_object = new Ball(component_manager_ref, inputmanager);
		ScrapEngineManager->logic_manager_view->register_game_object(ball_game_object);
		//Respawn box trigger under the map
		Trigger* box_trigger = new Trigger(component_manager_ref);
		ScrapEngineManager->logic_manager_view->register_game_object(box_trigger);
		box_trigger->add_collision_test(ball_game_object);
		//Terrain pieces
		WorldTerrainCreator* terrain_creator = new WorldTerrainCreator(component_manager_ref);
		delete terrain_creator;
		//Terrain objects
		WorldObjectsCreator* terrain_objects_creator = new WorldObjectsCreator(ScrapEngineManager->logic_manager_view,
		                                                                       ball_game_object);
		terrain_objects_creator->register_crates_to_trigger(box_trigger);
		delete terrain_objects_creator;
		//Create basic music object
		ScrapEngineManager->logic_manager_view->register_game_object(new Music(component_manager_ref));
		//Create the camera
		GameCamera* game_camera_ref = new GameCamera(inputmanager,
		                                           ScrapEngineManager->render_manager_view->get_default_render_camera(),
		                                           ball_game_object);
		game_camera_ref->set_game_window_ref(gameWindowRef);
		ScrapEngineManager->logic_manager_view->register_game_object(game_camera_ref);
		//Begin gameplay
		ScrapEngineManager->start_game_loop();
		//End gameplay
	}
	catch (const std::exception& e)
	{
		std::cerr << "EXCEPTION MESSAGE-->" << e.what() << std::endl;
		exit_value = EXIT_FAILURE;
	}
	//Delete
	delete ScrapEngineManager;
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
