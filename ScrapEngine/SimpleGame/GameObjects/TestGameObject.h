#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/Rendering/Manager/RenderManager.h"
#include "Engine/Input/Manager/InputManager.h"
#include "Engine/Input/KeyboardKeys.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class TestGameObject : public ScrapEngine::SGameObject
{
private:
	ScrapEngine::Input::InputManager* InputManagerRef;
	ScrapEngine::ComponentsManager* ComponentManagerRef;

	bool flipflop = false;
	float rotation = 1;
public:
	TestGameObject(ScrapEngine::Input::InputManager* CreatedInputManager, ScrapEngine::ComponentsManager* input_ComponentManager);
	~TestGameObject() = default;

	virtual void GameStart() override;
	virtual void GameUpdate(float time) override;

	void SpawnCrateAtLocation(glm::vec3 pos);
};

