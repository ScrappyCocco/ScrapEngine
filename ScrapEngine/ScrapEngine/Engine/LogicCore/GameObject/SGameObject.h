#pragma once

#include "../../Utility/UsefulTypes.h"
#include "../SObject.h"
#include "../Components/SComponent.h"
#include <vector>

namespace ScrapEngine {
	class SGameObject : public SObject
	{
	private:
		ScrapEngine::Transform ObjectTransform;
		bool isStatic = false;

		std::vector<ScrapEngine::SComponent*> ObjectComponents;
	public:
		SGameObject(const std::string& objectName, const ScrapEngine::Transform& input_ObjectTransform = ScrapEngine::Transform(), bool isStaticObject = false);
		~SGameObject() = 0;

		virtual void GameStart();
		virtual void GameUpdate(const float& time);

		void setObjectLocation(const glm::vec3& location);
		void setObjectRotation(const glm::vec3& rotation);
		void setObjectScale(const glm::vec3& scale);

		glm::vec3 getObjectLocation() const;
		glm::vec3 getObjectRotation() const;
		glm::vec3 getObjectScale() const;

		void AddComponent(SComponent* Component);
		const std::vector<SComponent*>* GetComponents();
	};
}
