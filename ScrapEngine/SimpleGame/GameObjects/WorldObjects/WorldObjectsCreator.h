#pragma once

#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include "../RespawnTrigger/Trigger.h"

class WorldObjectsCreator
{
private:
	void create_crate(const ScrapEngine::Core::SVector3& pos);
	void create_coin(const ScrapEngine::Core::SVector3& pos) const;
	//Creation methods
	void create_crates();
	void create_coins() const;
	//List of crates, used to add them to kill trigger
	std::list<ScrapEngine::Core::SGameObject*> crates_;
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_manager_ref_ = nullptr;
	ScrapEngine::Core::SGameObject* player_ref_ = nullptr;
public:
	WorldObjectsCreator(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
	                    ScrapEngine::Core::SGameObject* player);
	~WorldObjectsCreator() = default;

	void register_crates_to_trigger(Trigger* kill_trigger);
};

