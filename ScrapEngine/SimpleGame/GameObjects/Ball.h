#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Ball : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;
	ScrapEngine::Input::InputManager* InputManagerRef;

	ScrapEngine::Core::RigidBodyComponent* collider;
public:
	Ball(ScrapEngine::Core::ComponentsManager* input_ComponentManager,
	               ScrapEngine::Input::InputManager* CreatedInputManagerf);
	~Ball() = default;

	virtual void game_start() override;
	virtual void game_update(float time) override;
};
