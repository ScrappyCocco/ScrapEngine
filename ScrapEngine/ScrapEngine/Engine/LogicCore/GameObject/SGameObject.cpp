#include <Engine/LogicCore/GameObject/SGameObject.h>

ScrapEngine::Core::SGameObject::SGameObject(const std::string& object_name,
                                            const ScrapEngine::Transform& input_object_transform,
                                            const bool is_static_object) :
	SObject(object_name), object_transform_(input_object_transform), is_static_(is_static_object)
{
}

ScrapEngine::Core::SGameObject::~SGameObject()
{
	for (SComponent* component : object_components_)
	{
		delete component;
	}
}

void ScrapEngine::Core::SGameObject::game_start()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::game_update(float time)
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::set_object_location(const glm::vec3& location)
{
	object_transform_.location = location;
	//Update the transform of every component
	for (SComponent* component : object_components_)
	{
		component->set_father_transform(object_transform_);
		component->update_component_location();
	}
}

void ScrapEngine::Core::SGameObject::set_object_rotation(const glm::vec3& rotation)
{
	object_transform_.rotation = rotation;
	//Update the transform of every component
	for (SComponent* component : object_components_)
	{
		component->set_father_transform(object_transform_);
		component->update_component_rotation();
	}
}

void ScrapEngine::Core::SGameObject::set_object_scale(const glm::vec3& scale)
{
	object_transform_.scale = scale;
	//Update the transform of every component
	for (SComponent* component : object_components_)
	{
		component->set_father_transform(object_transform_);
		component->update_component_scale();
	}
}

glm::vec3 ScrapEngine::Core::SGameObject::get_object_location() const
{
	return object_transform_.location;
}

glm::vec3 ScrapEngine::Core::SGameObject::get_object_rotation() const
{
	return object_transform_.rotation;
}

glm::vec3 ScrapEngine::Core::SGameObject::get_object_scale() const
{
	return object_transform_.scale;
}

void ScrapEngine::Core::SGameObject::add_component(SComponent* component)
{
	object_components_.push_back(component);
	//Set component default values same as object
	component->set_component_location(object_transform_.location);
	component->set_component_rotation(object_transform_.rotation);
	component->set_component_scale(object_transform_.scale);
}

const std::vector<ScrapEngine::Core::SComponent*>* ScrapEngine::Core::SGameObject::get_components() const
{
	return &object_components_;
}
