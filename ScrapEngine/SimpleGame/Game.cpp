#define STB_IMAGE_IMPLEMENTATION
#include "Engine/Manager/EngineManager.h"

int main() {
	short exit_value = EXIT_SUCCESS;
	ScrapEngine::EngineManager* ScrapEngineManager = nullptr;
	try {
		//init engine
		ScrapEngineManager = new ScrapEngine::EngineManager("ScrapEngine Simple Game", 0);
		//More stuff

		//Begin gameplay
		ScrapEngineManager->StartGameLoop();
		//End
		std::cout << "EXIT_SUCCESS - Press to exit...";
	}catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "EXIT_FAILURE - Press to exit...";
		exit_value = EXIT_FAILURE;
	}
	delete ScrapEngineManager;
	getchar();
	fflush(stdin);
	return exit_value;

}