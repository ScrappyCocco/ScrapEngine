#pragma once

#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include "../RespawnTrigger/Trigger.h"
#include "../ScoreManager/ScoreManager.h"

class WorldObjectsCreator
{
private:
	void create_crate(const ScrapEngine::Core::SVector3& pos);
	void create_coin(const ScrapEngine::Core::SVector3& pos) const;
	void create_checkpoint(const ScrapEngine::Core::SVector3& pos) const;
	//Creation methods
	void create_crates();
	void create_coins() const;
	void create_checkpoints() const;
	//List of crates, used to add them to kill trigger
	std::list<ScrapEngine::Core::SGameObject*> crates_;
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_manager_ref_ = nullptr;
	Ball* player_ref_ = nullptr;
	ScoreManager* score_manager_ref_ = nullptr;
public:
	WorldObjectsCreator(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
	                    Ball* player,
	                    ScoreManager* score_manager);
	~WorldObjectsCreator() = default;

	void register_crates_to_trigger(Trigger* kill_trigger);
};
