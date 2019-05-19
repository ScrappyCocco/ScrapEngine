#pragma once

#include "../../Utility/UsefulTypes.h"
#include "../SObject.h"
#include "../Components/SComponent.h"
#include <vector>

namespace ScrapEngine
{
	namespace Core
	{
		class SGameObject : public Core::SObject
		{
		private:
			ScrapEngine::Transform object_transform_;
			bool is_static_ = false;

			std::vector<ScrapEngine::Core::SComponent*> object_components_;
		public:
			explicit SGameObject(const std::string& object_name,
			                     const ScrapEngine::Transform& input_object_transform = ScrapEngine::Transform(),
			                     bool is_static_object = false);
			~SGameObject() = 0;

			virtual void game_start();
			virtual void game_update(float time);

			void set_object_location(const glm::vec3& location);
			void set_object_rotation(const glm::vec3& rotation);
			void set_object_scale(const glm::vec3& scale);

			glm::vec3 get_object_location() const;
			glm::vec3 get_object_rotation() const;
			glm::vec3 get_object_scale() const;

			void add_component(SComponent* component);
			const std::vector<SComponent*>* get_components() const;
		};
	}
}
