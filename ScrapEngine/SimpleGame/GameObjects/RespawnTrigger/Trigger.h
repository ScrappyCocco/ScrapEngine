#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager;
		class RigidBodyComponent;
		class TriggerComponent;
	}
}

class Trigger final : public ScrapEngine::Core::SGameObject
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
