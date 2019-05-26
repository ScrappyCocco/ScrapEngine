#pragma once

#include <Engine/LogicCore/SObject.h>
#include <glm/glm.hpp>
#include <Engine/Utility/UsefulTypes.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SComponent : public Core::SObject
		{
		private:
			ScrapEngine::Transform father_transform_;
		protected:
			ScrapEngine::Transform object_relative_transform_;
			ScrapEngine::Transform object_world_transform_;
		public:
			explicit SComponent(const std::string& component_name);
			virtual ~SComponent() = 0;

			virtual void set_component_location(const glm::vec3& location);
			virtual void set_component_rotation(const glm::vec3& rotation);
			virtual void set_component_scale(const glm::vec3& scale);

			virtual void update_component_location();
			virtual void update_component_rotation();
			virtual void update_component_scale();

			void set_father_transform(const Transform& input_father_transform);

			virtual glm::vec3 get_component_location() const;
			virtual glm::vec3 get_component_rotation() const;
			virtual glm::vec3 get_component_scale() const;

			glm::vec3 get_component_relative_location() const;
			glm::vec3 get_component_relative_rotation() const;
			glm::vec3 get_component_relative_scale() const;
		};
	}
}
