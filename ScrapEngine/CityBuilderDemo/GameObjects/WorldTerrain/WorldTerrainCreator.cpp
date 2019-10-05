#include "WorldTerrainCreator.h"
#include "Terrain.h"

WorldTerrainCreator::WorldTerrainCreator(ScrapEngine::Core::ComponentsManager* input_component_manager)
{
	//Initial spawn platform
	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(0, 0, 0),
	            ScrapEngine::Core::SVector3(25, 0.5f, 25));

	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(0, 0, 0),
	            ScrapEngine::Core::SVector3(1, 1, 1),
	            Terrain::color::green);

	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(100, 0, 100),
	            ScrapEngine::Core::SVector3(1, 1, 1),
	            Terrain::color::yellow);

	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(100, 0, -100),
	            ScrapEngine::Core::SVector3(1, 1, 1),
	            Terrain::color::yellow);

	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(-100, 0, 100),
	            ScrapEngine::Core::SVector3(1, 1, 1),
	            Terrain::color::yellow);

	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(-100, 0, -100),
	            ScrapEngine::Core::SVector3(1, 1, 1),
	            Terrain::color::yellow);
}
