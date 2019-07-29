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
	std::vector<std::pair<SGameObject*, ScrapEngine::Core::RigidBodyComponent*>> elements_to_remove;
	for (auto object : test_collision_objects_)
	{
		if (box_trigger_->test_collision(object.second))
		{
			if (object.first->to_string() == "Ball game object")
			{
				//Respawn the ball
				object.first->respawn();
			}
			else
			{
				//Kill the fallen object
				elements_to_remove.push_back(object);
				object.first->die();
			}
		}
	}
	for (auto object : elements_to_remove)
	{
		const std::vector<std::pair<SGameObject*, ScrapEngine::Core::RigidBodyComponent*>>::iterator element =
			std::find(
				test_collision_objects_.begin(),
				test_collision_objects_.end(),
				object);
		if (element != test_collision_objects_.end())
		{
			test_collision_objects_.erase(element);
		}
	}
}
