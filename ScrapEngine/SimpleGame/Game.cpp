#include "Engine/Manager/EngineManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "GameObjects/TestGameObject.h"
#include "GameObjects/Camera/GameCamera.h"

int main() {
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::EngineManager* ScrapEngineManager = nullptr;
	try {
		//init engine
		ScrapEngineManager = new ScrapEngine::EngineManager("ScrapEngine Simple Chess Game", 0);
		ScrapEngine::GameWindow* gameWindowRef = ScrapEngineManager->RenderManagerView->getGameWindow();
		gameWindowRef->setWindowIcon("../assets/game_icon/chess_game_icon_png.png");
		//Create the input manager
		ScrapEngine::Input::InputManager* inputmanager = gameWindowRef->createWindowInputManager();
		inputmanager->set_cursor_input_mode(ScrapEngine::Input::cursor_mode::cursor_grabbed_mode);
		//Get the component manager
		ScrapEngine::Core::ComponentsManager* ComponentManagerRef = ScrapEngineManager->LogicManagerView->getComponentsManager();
		//Set the world skybox
		ScrapEngine::Core::SceneManager* SceneManagerRef = ScrapEngineManager->LogicManagerView->getSceneManager();
		SceneManagerRef->set_skybox(
			std::array<std::string, 6>{
				"../assets/skybox/spires_ft.png", //FRONT TEXTURE
				"../assets/skybox/spires_bk.png", //BACK TEXTURE
				"../assets/skybox/spires_up.png", //UP TEXTURE
				"../assets/skybox/spires_dn.png", //DOWN TEXTURE
				"../assets/skybox/spires_rt.png", //RIGHT TEXTURE
				"../assets/skybox/spires_lf.png", //LEFT TEXTURE
			}
		);
		SceneManagerRef->set_skybox_size(150);
		//Create the first game object
		TestGameObject* FirstGameObject = new TestGameObject(inputmanager, ComponentManagerRef);
		ScrapEngineManager->LogicManagerView->register_game_object(FirstGameObject);
		//Create the camera
		GameCamera* GameCameraRef = new GameCamera(inputmanager, ScrapEngineManager->RenderManagerView->getDefaultRenderCamera(), FirstGameObject);
		ScrapEngineManager->LogicManagerView->register_game_object(GameCameraRef);
		//Begin gameplay
		ScrapEngineManager->StartGameLoop();
		//End gameplay
	}catch (const std::exception& e) {
		std::cerr << "EXCEPTION MESSAGE-->" << e.what() << std::endl;
		exit_value = EXIT_FAILURE;
	}
	//Delete
	delete ScrapEngineManager;
	//Display error message
	if (exit_value == EXIT_FAILURE) { //Exit failure, whait to close
		std::cout << std::endl << "EXIT_FAILURE - Press to exit..." << std::endl;
		fflush(stdin);
		getchar();
	}
	else {
		std::cout << std::endl << "EXIT_SUCCESS" << std::endl;
	}
	//End of program
	return exit_value;
}