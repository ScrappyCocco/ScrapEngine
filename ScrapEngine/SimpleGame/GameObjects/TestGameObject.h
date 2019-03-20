#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/Rendering/Manager/RenderManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class TestGameObject : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Input::InputManager* InputManagerRef;
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;

	bool flipflop = false;
	float rotation = 1;
public:
	TestGameObject(ScrapEngine::Input::InputManager* CreatedInputManager, ScrapEngine::Core::ComponentsManager* input_ComponentManager);
	~TestGameObject() = default;

	virtual void game_start() override;
	virtual void game_update(float time) override;

};

