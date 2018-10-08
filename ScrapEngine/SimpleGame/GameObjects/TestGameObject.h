#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/Input/Manager/InputManager.h"

class TestGameObject : public ScrapEngine::SGameObject
{
private:
	ScrapEngine::InputManager* InputManagerRef;
public:
	TestGameObject(ScrapEngine::InputManager* CreatedInputManager);
	~TestGameObject();

	virtual void GameStart();
	virtual void GameUpdate();
};

