#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Terrain : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;

public:
	Terrain(ScrapEngine::Core::ComponentsManager* input_ComponentManager);
	~Terrain() = default;

};

