#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

class Trigger : public ScrapEngine::Core::SGameObject
{
private:
	//Trigger
	ScrapEngine::Core::TriggerComponent* box_trigger_;
	//Object to test collision
	std::vector<ScrapEngine::Core::RigidBodyComponent*> test_collision_objects_;
public:
	Trigger(ScrapEngine::Core::ComponentsManager* input_component_manager);
	~Trigger() = default;

	void add_collision_test(SGameObject* obj, int index = 1);

	void game_update(float time) override;
};
