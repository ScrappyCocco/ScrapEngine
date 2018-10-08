#pragma once

#include "../../Utility/UsefulTypes.h"
#include "../SObject.h"
#include "../Components/SComponent.h"
#include <vector>

namespace ScrapEngine {

	class SComponent;

	class SGameObject : public SObject
	{
	private:
		ScrapEngine::Transform ObjectTransform;
		bool isStatic = false;

		std::vector<ScrapEngine::SComponent*> ObjectComponents;
	public:
		SGameObject(std::string objectName, ScrapEngine::Transform input_ObjectTransform = ScrapEngine::Transform(), bool isStaticObject = false);
		~SGameObject() = 0;

		virtual void GameStart();
		virtual void GameUpdate();

		void AddComponent(SComponent* Component);
		const std::vector<SComponent*>* GetComponents();
	};

}

