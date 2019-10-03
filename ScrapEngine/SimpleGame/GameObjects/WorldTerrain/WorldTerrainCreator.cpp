#include "WorldTerrainCreator.h"
#include "Terrain.h"

WorldTerrainCreator::WorldTerrainCreator(ScrapEngine::Core::ComponentsManager* input_component_manager)
{
	//Initial spawn platform
	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(0, -20, 0),
	            ScrapEngine::Core::SVector3(25, 0.5f, 25));

	//First corridor
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(0, -20, -250),
		ScrapEngine::Core::SVector3(5, 0.5f, 25));

	//Respawn platform terrain
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(0, -20, -400),
		ScrapEngine::Core::SVector3(10, 0.5f, 10));

	//Respawn platform wall
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(0, -5, -449),
		ScrapEngine::Core::SVector3(10, 3, 0.5f));

	//First right corridor
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(150, -20, -400),
		ScrapEngine::Core::SVector3(25, 0.5f, 5));

	//UP
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(250, -20, -450),
		ScrapEngine::Core::SVector3(5, 0.5f, 10));

	//Right
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(350, -20, -475),
		ScrapEngine::Core::SVector3(15, 0.5f, 5));

	//Down
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(450, -20, -375),
		ScrapEngine::Core::SVector3(5, 0.5f, 25));

	//Wall(s)
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(435, -10, -400),
		ScrapEngine::Core::SVector3(2, 1.5f, 0.5f),
		Terrain::color::green);

	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(465, -10, -350),
		ScrapEngine::Core::SVector3(2, 1.5f, 0.5f),
		Terrain::color::green);

	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(450, -10, -300),
		ScrapEngine::Core::SVector3(2, 1.5f, 0.5f),
		Terrain::color::green);

	//Left terrain
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(400, -20, -225),
		ScrapEngine::Core::SVector3(15, 0.5f, 5));
	
	//Second respawn
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(275, -20, -225),
		ScrapEngine::Core::SVector3(10, 0.5f, 10));

	//Down
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(275, -20, -125),
		ScrapEngine::Core::SVector3(5, 0.5f, 10));

	//Right
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(375, -20, -100),
		ScrapEngine::Core::SVector3(15, 0.5f, 5));

	//Down
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(425, -20, -25),
		ScrapEngine::Core::SVector3(5, 0.5f, 10));

	//Finish
	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(425, -20, 75),
		ScrapEngine::Core::SVector3(10, 0.01f, 10),
		Terrain::color::finish);
}
