#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Components/Manager/ComponentsManager.h"

class Music : public ScrapEngine::Core::SGameObject
{
private:
	ScrapEngine::Core::AudioComponent* audio_;
public:
	Music(ScrapEngine::Core::ComponentsManager* input_component_manager);
	~Music() = default;

	void game_start() override;
};
