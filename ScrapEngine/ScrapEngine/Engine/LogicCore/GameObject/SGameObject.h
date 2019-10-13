#pragma once

#include <Engine/LogicCore/SObject.h>
#include <Engine/LogicCore/Components/SComponent.h>
#include <vector>

namespace ScrapEngine
{
	namespace Core
	{
		//Forward declaration to avoid include-loop
		class SComponent;
		
		class SGameObject : public SObject
		{
			//Friend class to update relative transform
			//Accessing private methods the user shouldn't see and use
			friend class SComponent;
		private:
			STransform object_transform_;
			STransform object_relative_transform_;
			bool should_update_ = true;

			std::vector<SComponent*> object_components_;
			std::vector<SGameObject*> object_child_;
			SGameObject* father_object_ = nullptr;
		public:
			explicit SGameObject(const std::string& object_name,
			                     const STransform& input_object_transform = STransform());
			~SGameObject() = 0;

			//Basics events
			virtual void game_start();
			virtual void game_update(float time);
			virtual void on_gui();

			//More events the user can decide to define
			//None of these is called by the engine
			//These are called and defined by you when needed
			virtual void spawn();
			virtual void respawn();
			virtual void die();
			virtual void kill();

			void set_should_update(bool should_update);
			bool get_should_update() const;

			//The should_update_relative is false when the value is updated from an update() call
			void set_object_location(const SVector3& location, bool should_update_relative = true);
			void set_object_rotation(const SVector3& rotation, bool should_update_relative = true);
			void set_object_scale(const SVector3& scale, bool should_update_relative = true);
			void add_object_rotation(const SVector3& rotation);

			SVector3 get_object_location() const;
			SVector3 get_object_rotation() const;
			SVector3 get_object_scale() const;

			void add_component(SComponent* component);
			void remove_component(SComponent* component);
			const std::vector<SComponent*>* get_components() const;

			void add_child(SGameObject* game_object);
			void remove_child(SGameObject* game_object);
			const std::vector<SGameObject*>* get_child() const;
		private:
			//Update the relative values based on father_object_ transform
			virtual void update_relative_location();
			virtual void update_relative_rotation();
			virtual void update_relative_scale();
			
			virtual void update_object_location();
			virtual void update_object_rotation();
			virtual void update_object_scale();
		};
	}
}
