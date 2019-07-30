#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Terrain : public ScrapEngine::Core::SGameObject
{
public:
	enum color
	{
		red,
		white,
		green,
		finish
	};

	Terrain(ScrapEngine::Core::ComponentsManager* input_component_manager,
	        const ScrapEngine::Core::SVector3& position,
	        const ScrapEngine::Core::SVector3& scale,
	        color c = white);
	~Terrain() = default;
};
