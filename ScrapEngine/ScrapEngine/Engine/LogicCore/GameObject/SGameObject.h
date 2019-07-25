#pragma once

#include <Engine/LogicCore/SObject.h>
#include <Engine/LogicCore/Components/SComponent.h>
#include <vector>

namespace ScrapEngine
{
	namespace Core
	{
		class SGameObject : public SObject
		{
		private:
			STransform object_transform_;
			STransform object_relative_transform_;
			bool should_update = true;

			std::vector<SComponent*> object_components_;
			std::vector<SGameObject*> object_child_;
			SGameObject* father_object_ = nullptr;
		public:
			explicit SGameObject(const std::string& object_name,
			                     const STransform& input_object_transform = STransform());
			~SGameObject() = 0;

			virtual void game_start();
			virtual void game_update(float time);
			//Note: on_gui() is not called on the main thread
			//Will be called on different times than game_update()
			//If you have variables to update do it on game_update()
			virtual void on_gui();

			void set_should_update(bool should_update);
			bool get_should_update() const;

			//The should_update_relative is false when the value is updated from an update() call
			void set_object_location(const SVector3& location, bool should_update_relative = true);
			void set_object_rotation(const SVector3& rotation, bool should_update_relative = true);
			void set_object_scale(const SVector3& scale, bool should_update_relative = true);

			SVector3 get_object_location() const;
			SVector3 get_object_rotation() const;
			SVector3 get_object_scale() const;

			//Update the relative values based on father_object_ transform
			virtual void update_relative_transform();
			virtual void update_object_location();
			virtual void update_object_rotation();
			virtual void update_object_scale();

			void add_component(SComponent* component);
			void remove_component(SComponent* component);
			const std::vector<SComponent*>* get_components() const;

			void add_child(SGameObject* game_object);
			void remove_child(SGameObject* game_object);
			const std::vector<SGameObject*>* get_child() const;
		};
	}
}
