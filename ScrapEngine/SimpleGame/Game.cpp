#include <iostream>
#include <Engine/Manager/EngineManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include "GameObjects/Camera/GameCamera.h"
#include "GameObjects/Player/Ball.h"
#include "GameObjects/RespawnTrigger/Trigger.h"
#include "GameObjects/FinishTriggerMenu/FinishMenu.h"
#include "GameObjects/Music/Music.h"
#include "GameObjects/WorldTerrain/WorldTerrainCreator.h"
#include "GameObjects/WorldObjects/WorldObjectsCreator.h"
#include "GameObjects/MainMenu/MainMenu.h"
#include "GameObjects/ScoreManager/ScoreManager.h"

int main()
{
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::Manager::EngineManager* scrap_engine_manager = nullptr;
	try
	{
		//Init engine
		scrap_engine_manager = new ScrapEngine::Manager::EngineManager("Example Game", 0, 1280, 720);
		ScrapEngine::Render::GameWindow* game_window_ref = scrap_engine_manager->render_manager_view->get_game_window();
		game_window_ref->set_window_icon("../assets/game_icon/crate_icon.png");
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
		//Set sun position and look at
		scene_manager_ref->set_light_pos(ScrapEngine::Core::SVector3(633.388f, 573.284f, 650.502f));
		scene_manager_ref->set_light_lookat(ScrapEngine::Core::SVector3(120.029f, -163.63f, -275.356f));
		//Set world gravity
		component_manager_ref->set_gravity(ScrapEngine::Core::SVector3(0, -50, 0));
		//Create the first game object
		//Ball - Player
		Ball* ball_game_object = new Ball(component_manager_ref, inputmanager);
		scrap_engine_manager->logic_manager_view->register_game_object(ball_game_object);
		//Respawn box trigger under the map
		Trigger* box_trigger = new Trigger(component_manager_ref);
		scrap_engine_manager->logic_manager_view->register_game_object(box_trigger);
		box_trigger->add_collision_test(ball_game_object);
		//Score manager
		ScoreManager* score_manager = new ScoreManager(ball_game_object, game_window_ref);
		scrap_engine_manager->logic_manager_view->register_game_object(score_manager);
		//Finish trigger
		scrap_engine_manager->logic_manager_view->register_game_object(new FinishTriggerMenu(
				scrap_engine_manager->logic_manager_view,
				ball_game_object,
				game_window_ref, score_manager)
		);
		//Terrain pieces
		WorldTerrainCreator* terrain_creator = new WorldTerrainCreator(component_manager_ref);
		delete terrain_creator;
		//Terrain objects
		WorldObjectsCreator* terrain_objects_creator = new WorldObjectsCreator(scrap_engine_manager->logic_manager_view,
		                                                                       ball_game_object,
		                                                                       score_manager);
		terrain_objects_creator->register_crates_to_trigger(box_trigger);
		delete terrain_objects_creator;
		//Create basic music object
		scrap_engine_manager->logic_manager_view->register_game_object(new Music(component_manager_ref));
		//Create the camera
		GameCamera* game_camera_ref = new GameCamera(inputmanager,
		                                             component_manager_ref,
		                                             ball_game_object);
		game_camera_ref->set_game_window_ref(game_window_ref);
		scrap_engine_manager->logic_manager_view->register_game_object(game_camera_ref);
		//MainMenu
		scrap_engine_manager->logic_manager_view->register_game_object(new MainMenu(
			scrap_engine_manager->logic_manager_view,
			ball_game_object, game_window_ref, inputmanager));
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
		//Exit failure, wait to close
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
