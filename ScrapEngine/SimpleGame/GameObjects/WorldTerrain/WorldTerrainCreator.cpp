#include "WorldTerrainCreator.h"
#include "Terrain.h"

WorldTerrainCreator::WorldTerrainCreator(ScrapEngine::Core::ComponentsManager* input_component_manager)
{
	//Initial spawn platform
	new Terrain(input_component_manager,
	            ScrapEngine::Core::SVector3(0, -20, 0),
	            ScrapEngine::Core::SVector3(25, 0.5f, 25));

	new Terrain(input_component_manager,
		ScrapEngine::Core::SVector3(0, -20, -250),
		ScrapEngine::Core::SVector3(5, 0.5f, 25));
}
