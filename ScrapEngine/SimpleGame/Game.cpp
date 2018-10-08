#include "Engine/Manager/EngineManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "GameObjects/TestGameObject.h"

int main() {
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::EngineManager* ScrapEngineManager = nullptr;
	try {
		//init engine
		ScrapEngineManager = new ScrapEngine::EngineManager("ScrapEngine Simple Chess Game", 0);
		const ScrapEngine::GameWindow* gameWindowRef = ScrapEngineManager->getGameWindow();
		gameWindowRef->setWindowIcon("../assets/game_icon/chess_game_icon_png.png");
		//More stuff
		ScrapEngine::InputManager* inputmanager = gameWindowRef->createWindowInputManager();
		TestGameObject* FirstGameObject = new TestGameObject(inputmanager);
		ScrapEngineManager->getLogicManager()->RegisterGameObject(FirstGameObject);
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
	getchar();
	fflush(stdin);
	return exit_value;

}