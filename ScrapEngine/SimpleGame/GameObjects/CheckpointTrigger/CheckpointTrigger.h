#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"

namespace ScrapEngine
{
	namespace Core
	{
		class LogicManagerView;
		class TriggerComponent;
	}
}

class CheckpointTrigger final : public ScrapEngine::Core::SGameObject
{
private:
	//Player
	Ball* player_ref_ = nullptr;
	//Trigger
	ScrapEngine::Core::TriggerComponent* box_trigger_;
	//Object to test collision
	ScrapEngine::Core::RigidBodyComponent* test_collision_object_;
	//Initial position
	ScrapEngine::Core::SVector3 pos_;

	bool in_trigger_ = false;
	float timer_ = 0;
public:
	CheckpointTrigger(ScrapEngine::Core::LogicManagerView* logic_view,
	                  Ball* player, const ScrapEngine::Core::SVector3& pos);
	~CheckpointTrigger() = default;

	void game_update(float time) override;
	void on_gui() override;
};
