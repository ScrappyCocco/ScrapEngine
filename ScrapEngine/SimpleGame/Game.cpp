#include "Engine/Manager/EngineManager.h"

int main() {
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::EngineManager* ScrapEngineManager = nullptr;
	try {
		//init engine
		ScrapEngineManager = new ScrapEngine::EngineManager("ScrapEngine Simple Chess Game", 0);
		const ScrapEngine::GameWindow* gameWindowRef = ScrapEngineManager->getRenderManager()->getGameWindow();
		gameWindowRef->setWindowIcon(1, &gameWindowRef->loadIcon("../assets/game_icon/chess_game_icon_png.png"));
		//More stuff

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