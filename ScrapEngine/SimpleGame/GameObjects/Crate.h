#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Crate : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;

public:
	Crate(ScrapEngine::Core::ComponentsManager* input_ComponentManager, const ScrapEngine::Core::SVector3& start_pos);
	~Crate() = default;

};

