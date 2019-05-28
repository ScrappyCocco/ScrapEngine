#pragma once

#include <Engine/Utility/UsefulTypes.h>
#include <Engine/LogicCore/SObject.h>
#include <Engine/LogicCore/Components/SComponent.h>
#include <vector>

namespace ScrapEngine
{
	namespace Core
	{
		class SGameObject : public Core::SObject
		{
		protected:
			ScrapEngine::Transform object_transform_;
			ScrapEngine::Transform object_relative_transform_;
			bool is_static_ = false;

			std::vector<ScrapEngine::Core::SComponent*> object_components_;
			std::vector<ScrapEngine::Core::SGameObject*> object_child_;
			ScrapEngine::Core::SGameObject* father_object_ = nullptr;
		public:
			explicit SGameObject(const std::string& object_name,
			                     const ScrapEngine::Transform& input_object_transform = ScrapEngine::Transform(),
			                     bool is_static_object = false);
			~SGameObject() = 0;

			virtual void game_start();
			virtual void game_update(float time);

			void set_object_location(const glm::vec3& location, bool should_update_relative = true);
			void set_object_rotation(const glm::vec3& rotation, bool should_update_relative = true);
			void set_object_scale(const glm::vec3& scale, bool should_update_relative = true);

			glm::vec3 get_object_location() const;
			glm::vec3 get_object_rotation() const;
			glm::vec3 get_object_scale() const;

			virtual void update_relative_transform();
			virtual void update_object_location();
			virtual void update_object_rotation();
			virtual void update_object_scale();

			void add_component(SComponent* component);
			void remove_component(SComponent* component);
			const std::vector<SComponent*>* get_components() const;

			void add_child(SGameObject* game_object);
			void remove_child(SGameObject* game_object);
			const std::vector<ScrapEngine::Core::SGameObject*>* get_child() const;
		};
	}
}
