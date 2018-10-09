#pragma once

#include "../SObject.h"
#include "../GameObject/SGameObject.h"

namespace ScrapEngine {

	class SGameObject;

	class SComponent : public SObject
	{
	private:

	public:
		SComponent(std::string componentName);
		~SComponent() = 0;

		virtual void setComponentLocation(glm::vec3 location);
		virtual void setComponentRotation(glm::vec3 rotation);
		virtual void setComponentScale(glm::vec3 scale);

		virtual glm::vec3 getComponentLocation();
		virtual glm::vec3 getComponentRotation();
		virtual glm::vec3 getComponentScale();
	};

}

