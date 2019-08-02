#include "Trigger.h"

Trigger::Trigger(ScrapEngine::Core::ComponentsManager* input_component_manager)
	: SGameObject("Trigger test game object"), component_manager_ref_(input_component_manager)
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
		std::pair<SGameObject*, ScrapEngine::Core::RigidBodyComponent*> pair_to_add;
		pair_to_add.first = obj;
		pair_to_add.second = component;
		test_collision_objects_.push_back(pair_to_add);
	}
}

void Trigger::game_update(float time)
{
	std::vector<std::pair<SGameObject*, ScrapEngine::Core::RigidBodyComponent*>> test_collision_objects_clean;
	for (auto object : test_collision_objects_)
	{
		if (box_trigger_->test_collision(object.second))
		{
			if (object.first->to_string() == "Ball game object")
			{
				//Respawn the ball
				object.first->respawn();
				//And keep it in the list
				test_collision_objects_clean.push_back(object);
			}
			else
			{
				//Kill the fallen object
				object.first->die();
			}
		}else
		{
			//If the object is not in the trigger re-add it to the list
			test_collision_objects_clean.push_back(object);
		}
	}
	test_collision_objects_ = test_collision_objects_clean;
}
