#pragma once

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager;
	}
}

class WorldTerrainCreator
{
public:
	WorldTerrainCreator(ScrapEngine::Core::ComponentsManager* input_component_manager);
	~WorldTerrainCreator() = default;
};
