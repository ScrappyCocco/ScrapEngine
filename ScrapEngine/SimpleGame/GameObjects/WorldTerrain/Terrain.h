#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Terrain : public ScrapEngine::Core::SGameObject
{
private:
	//utils
	ScrapEngine::Core::ComponentsManager* component_manager_ref_;
public:
	Terrain(ScrapEngine::Core::ComponentsManager* input_component_manager,
	        const ScrapEngine::Core::SVector3& position,
	        const ScrapEngine::Core::SVector3& scale);
	~Terrain() = default;

};

