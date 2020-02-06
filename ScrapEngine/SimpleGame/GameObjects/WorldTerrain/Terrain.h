#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager;
		class MeshComponent;
	}
}

class Terrain : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::MeshComponent* mesh_ = nullptr;
public:
	enum class color
	{
		white,
		green,
		finish
	};

	Terrain(ScrapEngine::Core::ComponentsManager* input_component_manager,
	        const ScrapEngine::Core::SVector3& position,
	        const ScrapEngine::Core::SVector3& scale,
	        color c = color::white);
	~Terrain() = default;

	void disable_shadows() const;
	void enable_shadows() const;
};
