#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace ScrapEngine
{
	namespace Core
	{
		class ComponentsManager;
		class AudioComponent;
	}
}

class Music final : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::AudioComponent* audio_;
public:
	Music(ScrapEngine::Core::ComponentsManager* input_component_manager);
	~Music() = default;

	void game_start() override;
};
