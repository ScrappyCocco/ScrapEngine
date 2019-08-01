#pragma once

#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

class WorldTerrainCreator
{
private:
	//Utils
	ScrapEngine::Core::ComponentsManager* component_manager_ref_;
public:
	WorldTerrainCreator(ScrapEngine::Core::ComponentsManager* input_component_manager);
	~WorldTerrainCreator() = default;
};

