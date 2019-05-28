#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class AnotherTestGameObject : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;

public:
	AnotherTestGameObject(ScrapEngine::Core::ComponentsManager* input_ComponentManager);
	~AnotherTestGameObject() = default;

	virtual void game_start() override;
	virtual void game_update(float time) override;

};

