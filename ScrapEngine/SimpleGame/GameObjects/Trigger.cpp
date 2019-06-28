#include "Trigger.h"
#include <Engine/Debug/DebugLog.h>

Trigger::Trigger(ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager)
{
	box_trigger = input_ComponentManager->create_box_trigger_component(
		ScrapEngine::Core::SVector3(2500, 10, 2500),
		ScrapEngine::Core::SVector3(0, -150, 0));
}

void Trigger::add_collision_test(SGameObject* obj, const int index)
{
	ScrapEngine::Core::RigidBodyComponent* component = nullptr;
	component = dynamic_cast<ScrapEngine::Core::RigidBodyComponent*>((*obj->get_components())[index]);
	if (component) {
		test_collision_objects_.push_back(component);
	}
}

void Trigger::game_update(float time)
{
	for(ScrapEngine::Core::RigidBodyComponent* component : test_collision_objects_)
	{
		if (box_trigger->test_collision(component))
		{
			component->cancel_rigidbody_forces();
			component->modify_rigidbody_location(ScrapEngine::Core::SVector3(0, 20, 0));
		}
	}
}
