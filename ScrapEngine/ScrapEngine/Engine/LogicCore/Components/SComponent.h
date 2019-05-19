#pragma once

#include <Engine/LogicCore/SObject.h>
#include <glm/glm.hpp>

namespace ScrapEngine
{
	namespace Core
	{
		class SComponent : public Core::SObject
		{
		private:

		public:
			explicit SComponent(const std::string& component_name);
			virtual ~SComponent() = 0;

			virtual void set_component_location(const glm::vec3& location);
			virtual void set_component_rotation(const glm::vec3& rotation);
			virtual void set_component_scale(const glm::vec3& scale);

			virtual glm::vec3 get_component_location() const;
			virtual glm::vec3 get_component_rotation() const;
			virtual glm::vec3 get_component_scale() const;
		};
	}
}
