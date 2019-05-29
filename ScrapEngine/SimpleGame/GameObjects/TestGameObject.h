#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class TestGameObject : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;

public:
	TestGameObject(ScrapEngine::Core::ComponentsManager* input_ComponentManager);
	~TestGameObject() = default;

	virtual void game_start() override;
	virtual void game_update(float time) override;

};

