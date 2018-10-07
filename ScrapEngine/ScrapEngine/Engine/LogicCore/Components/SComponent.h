#pragma once

#include "../SObject.h"
#include "../GameObject/SGameObject.h"

namespace ScrapEngine {

	class SGameObject;

	class SComponent : public SObject
	{
	private:
		ScrapEngine::SGameObject* Parent = nullptr;
	public:
		SComponent(std::string componentName, SGameObject* ComponentParent);
		~SComponent() = 0;
	};

}

