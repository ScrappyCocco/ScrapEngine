#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Trigger : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::ComponentsManager* ComponentManagerRef;

	ScrapEngine::Core::TriggerComponent* box_trigger;

	std::vector<ScrapEngine::Core::RigidBodyComponent*> test_collision_objects_;
public:
	Trigger(ScrapEngine::Core::ComponentsManager* input_ComponentManager);
	~Trigger() = default;

	void add_collision_test(SGameObject* obj, int index = 1);

	void game_update(float time) override;
};

