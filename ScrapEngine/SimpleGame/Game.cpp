#include "Engine/Manager/EngineManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "GameObjects/TestGameObject.h"

int main() {
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::EngineManager* ScrapEngineManager = nullptr;
	try {
		//init engine
		ScrapEngineManager = new ScrapEngine::EngineManager("ScrapEngine Simple Chess Game", 0);
		ScrapEngine::GameWindow* gameWindowRef = ScrapEngineManager->RenderManagerView->getGameWindow();
		gameWindowRef->setWindowIcon("../assets/game_icon/chess_game_icon_png.png");
		//Create the input manager
		ScrapEngine::InputManager* inputmanager = gameWindowRef->createWindowInputManager();
		//Get the component manager
		ScrapEngine::ComponentsManager* ComponentManagerRef = ScrapEngineManager->LogicManagerView->getComponentsManager();
		//Create the first game object
		TestGameObject* FirstGameObject = new TestGameObject(inputmanager, ComponentManagerRef);
		ScrapEngineManager->LogicManagerView->RegisterGameObject(FirstGameObject);
		//Begin gameplay
		ScrapEngineManager->StartGameLoop();
		//End gameplay
		std::cout << "EXIT_SUCCESS - Press to exit..." << std::endl;
	}catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "EXIT_FAILURE - Press to exit..." << std::endl;
		exit_value = EXIT_FAILURE;
	}
	delete ScrapEngineManager;
	return exit_value;

}