#pragma once

#include "../SObject.h"
#include <glm/glm.hpp>

namespace ScrapEngine {
	class SComponent : public SObject
	{
	private:

	public:
		SComponent(std::string componentName);
		~SComponent() = 0;

		virtual void setComponentLocation(const glm::vec3& location);
		virtual void setComponentRotation(const glm::vec3& rotation);
		virtual void setComponentScale(const glm::vec3& scale);

		virtual glm::vec3 getComponentLocation() const;
		virtual glm::vec3 getComponentRotation() const;
		virtual glm::vec3 getComponentScale() const;
	};
}

