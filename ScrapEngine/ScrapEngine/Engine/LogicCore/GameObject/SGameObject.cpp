#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/LogicCore/Components/SComponent.h>
#include <algorithm>

ScrapEngine::Core::SGameObject::SGameObject(const std::string& object_name,
                                            const STransform& input_object_transform)
	: SObject(object_name), object_transform_(input_object_transform)
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

void ScrapEngine::Core::SGameObject::on_gui()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::spawn()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::respawn()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::die()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::kill()
{
	//This will be defined by the user when is necessary, otherwise it will have no effect
}

void ScrapEngine::Core::SGameObject::set_should_update(const bool should_update)
{
	this->should_update_ = should_update;
}

bool ScrapEngine::Core::SGameObject::get_should_update() const
{
	return should_update_;
}

void ScrapEngine::Core::SGameObject::set_object_location(const SVector3& location, const bool should_update_relative)
{
	object_transform_.set_position(location);
	//Check if i should update the relative values
	if (should_update_relative)
	{
		update_relative_location();
	}
	//Update the transform of every component
	for (SComponent* component : object_components_)
	{
		component->update_component_location();
	}
	//Update the transform of every child
	for (SGameObject* child_object : object_child_)
	{
		child_object->update_object_location();
	}
}

void ScrapEngine::Core::SGameObject::set_object_rotation(const SVector3& rotation, const bool should_update_relative)
{
	object_transform_.set_rotation(rotation);
	//Check if i should update the relative values
	if (should_update_relative)
	{
		update_relative_rotation();
	}
	//Update the transform of every component
	for (SComponent* component : object_components_)
	{
		component->update_component_rotation();
	}
	//Update the transform of every child
	for (SGameObject* child_object : object_child_)
	{
		child_object->update_object_rotation();
	}
}

void ScrapEngine::Core::SGameObject::set_object_scale(const SVector3& scale, const bool should_update_relative)
{
	object_transform_.set_scale(scale);
	//Check if i should update the relative values
	if (should_update_relative)
	{
		update_relative_scale();
	}
	//Update the transform of every component
	for (SComponent* component : object_components_)
	{
		component->update_component_scale();
	}
	//Update the transform of every child
	for (SGameObject* child_object : object_child_)
	{
		child_object->update_object_scale();
	}
}

void ScrapEngine::Core::SGameObject::add_object_rotation(const SVector3& rotation)
{
	object_transform_.add_rotation(rotation);

	update_relative_rotation();
	//Update the rotation
	set_object_rotation(get_object_rotation());
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SGameObject::get_object_location() const
{
	return object_transform_.get_position();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SGameObject::get_object_rotation() const
{
	return object_transform_.get_rotation();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SGameObject::get_object_scale() const
{
	return object_transform_.get_scale();
}

void ScrapEngine::Core::SGameObject::update_relative_location()
{
	if (father_object_)
	{
		object_relative_transform_.set_position(
			object_transform_.get_position() - father_object_->object_transform_.get_position());
	}
}

void ScrapEngine::Core::SGameObject::update_relative_rotation()
{
	if (father_object_)
	{
		object_relative_transform_.set_rotation(
			father_object_->object_transform_.get_quat_rotation().get_inverse() *
			object_transform_.get_quat_rotation()
		);
	}
}

void ScrapEngine::Core::SGameObject::update_relative_scale()
{
	if (father_object_)
	{
		object_relative_transform_.set_scale(
			object_transform_.get_scale() - father_object_->object_transform_.get_scale());
	}
}

void ScrapEngine::Core::SGameObject::update_object_location()
{
	const glm::mat4 local_m = generate_unscaled_transform_matrix(object_relative_transform_);
	const glm::mat4 father_m = generate_unscaled_transform_matrix(father_object_->object_transform_);
	const glm::mat4 full_m = father_m * local_m;

	const glm::vec3 pos = glm::vec3(full_m[3][0], full_m[3][1], full_m[3][2]);

	set_object_location(SVector3(pos), false);
}

void ScrapEngine::Core::SGameObject::update_object_rotation()
{
	object_transform_.set_rotation(
		father_object_->object_transform_.get_quat_rotation() * object_relative_transform_.get_quat_rotation()
	);
	set_object_rotation(object_transform_.get_rotation(), false);

	//Update location based on new rotation
	update_object_location();
}

void ScrapEngine::Core::SGameObject::update_object_scale()
{
	object_transform_.set_scale(father_object_->object_transform_.get_scale() + object_relative_transform_.get_scale());
}

void ScrapEngine::Core::SGameObject::add_component(SComponent* component, const bool update_position)
{
	object_components_.push_back(component);
	component->owner_ = this;
	if (update_position)
	{
		//Set component default values same as object
		component->set_component_location(object_transform_.get_position());
		component->set_component_rotation(object_transform_.get_rotation());
		component->set_component_scale(object_transform_.get_scale());
	}
}

void ScrapEngine::Core::SGameObject::remove_component(SComponent* component)
{
	object_components_.erase(std::remove(
		                         object_components_.begin(),
		                         object_components_.end(),
		                         component),
	                         object_components_.end());
	component->owner_ = nullptr;
}

const std::vector<ScrapEngine::Core::SComponent*>* ScrapEngine::Core::SGameObject::get_components() const
{
	return &object_components_;
}

void ScrapEngine::Core::SGameObject::add_child(SGameObject* game_object)
{
	object_child_.push_back(game_object);
	game_object->father_object_ = this;
	//Update relative
	game_object->update_relative_location();
	game_object->update_relative_rotation();
	game_object->update_relative_scale();
}

void ScrapEngine::Core::SGameObject::remove_child(SGameObject* game_object)
{
	object_child_.erase(std::remove(
		                    object_child_.begin(),
		                    object_child_.end(),
		                    game_object),
	                    object_child_.end());
	game_object->father_object_ = nullptr;
}

const std::vector<ScrapEngine::Core::SGameObject*>* ScrapEngine::Core::SGameObject::get_child() const
{
	return &object_child_;
}

ScrapEngine::Core::SGameObject* ScrapEngine::Core::SGameObject::get_father() const
{
	return father_object_;
}
