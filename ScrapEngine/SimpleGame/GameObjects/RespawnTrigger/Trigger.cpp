#include "Trigger.h"

Trigger::Trigger(ScrapEngine::Core::ComponentsManager* input_component_manager)
	: SGameObject("Trigger test game object")
{
	box_trigger_ = input_component_manager->create_box_trigger_component(
		ScrapEngine::Core::SVector3(2500, 10, 2500),
		ScrapEngine::Core::SVector3(0, -150, 0));
}

void Trigger::add_collision_test(SGameObject* obj, const int index)
{
	ScrapEngine::Core::RigidBodyComponent* component = nullptr;
	component = dynamic_cast<ScrapEngine::Core::RigidBodyComponent*>((*obj->get_components())[index]);
	if (component)
	{
		test_collision_objects_.push_back(component);
	}
}

void Trigger::game_update(float time)
{
	std::vector<ScrapEngine::Core::RigidBodyComponent*> test_collision_objects_clean;
	for (auto collsion_comp : test_collision_objects_)
	{
		if (box_trigger_->test_collision(collsion_comp))
		{
			if (collsion_comp->get_owner()->to_string() == "Ball game object")
			{
				//Respawn the ball
				collsion_comp->get_owner()->respawn();
				//And keep it in the list
				test_collision_objects_clean.push_back(collsion_comp);
			}
			else
			{
				//Kill the fallen object
				collsion_comp->get_owner()->die();
			}
		}
		else
		{
			//If the object is not in the trigger re-add it to the list
			test_collision_objects_clean.push_back(collsion_comp);
		}
	}
	test_collision_objects_ = std::move(test_collision_objects_clean);
}
