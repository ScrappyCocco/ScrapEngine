#include "WorldObjectsCreator.h"
#include "Crate.h"
#include "Coin.h"
#include "../CheckpointTrigger/CheckpointTrigger.h"
#include <Engine/LogicCore/Manager/LogicManagerView.h>

void WorldObjectsCreator::create_crate(const ScrapEngine::Core::SVector3& pos)
{
	crates_.push_back(new Crate(logic_manager_ref_, pos));
}

void WorldObjectsCreator::create_coin(const ScrapEngine::Core::SVector3& pos) const
{
	Coin* coin = new Coin(logic_manager_ref_, pos, score_manager_ref_);
	coin->set_collision_test(player_ref_);
	logic_manager_ref_->register_game_object(coin);
}

void WorldObjectsCreator::create_checkpoint(const ScrapEngine::Core::SVector3& pos) const
{
	logic_manager_ref_->register_game_object(new CheckpointTrigger(logic_manager_ref_, player_ref_, pos));
}

void WorldObjectsCreator::create_crates()
{
	// First group in the spawn platform
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(70, -10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(80, -10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(60, -10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(75, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(65, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(70, 10, -50)));
	// Second group in the spawn platform
	crates_.push_back(new Crate(logic_manager_ref_,
	                            ScrapEngine::Core::SVector3(-70, 0, -50),
	                            ScrapEngine::Core::SVector3(4, 4, 4),
	                            20));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-70, 25, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-45, -10, -35)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-90, -10, -20)));
	//First block of blocking crates after the first checkpoint
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(150, -10, -400)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(150, -10, -415)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(150, -10, -385)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(150, 5, -407)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(150, 5, -393)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(150, 15, -400)));
	//Crates near the obstacles
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(435, -10, -350)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(435, 0, -350)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(435, 10, -350)));
	//Second block of blocking crates after the first checkpoint
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(400, -10, -225)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(400, -10, -235)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(400, -10, -215)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(400, 5, -220)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(400, 5, -230)));
	//Last huge block of crates
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(375, -10, -90)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(375, -10, -110)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(365, -10, -90)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(365, -10, -110)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(375, 0, -90)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(375, 0, -110)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(365, 0, -90)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(365, 0, -110)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(370, 15, -100)));
}

void WorldObjectsCreator::create_coins() const
{
	//First corridor
	create_coin(ScrapEngine::Core::SVector3(0, -10, -150));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -200));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -250));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -300));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -350));
	//After first respawn
	create_coin(ScrapEngine::Core::SVector3(75, -10, -400));
	create_coin(ScrapEngine::Core::SVector3(100, -10, -400));
	//Second right terrain after first respawn
	create_coin(ScrapEngine::Core::SVector3(300, -10, -475));
	create_coin(ScrapEngine::Core::SVector3(350, -10, -475));
	create_coin(ScrapEngine::Core::SVector3(400, -10, -475));
	create_coin(ScrapEngine::Core::SVector3(470, -10, -500));
	//Before second respawn
	create_coin(ScrapEngine::Core::SVector3(350, -10, -225));
	//Before crates after second respawn
	create_coin(ScrapEngine::Core::SVector3(325, -10, -100));
	//Last coins on angles
	create_coin(ScrapEngine::Core::SVector3(250, -10, -70));
	create_coin(ScrapEngine::Core::SVector3(450, -10, -120));
}

void WorldObjectsCreator::create_checkpoints() const
{
	create_checkpoint(ScrapEngine::Core::SVector3(0, -18, -400));
	create_checkpoint(ScrapEngine::Core::SVector3(275, -18, -225));
}

WorldObjectsCreator::WorldObjectsCreator(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
                                         Ball* player,
                                         ScoreManager* score_manager)
	: logic_manager_ref_(logic_manager_ref), player_ref_(player), score_manager_ref_(score_manager)
{
	create_crates();
	create_coins();
	create_checkpoints();
}

void WorldObjectsCreator::register_crates_to_trigger(Trigger* kill_trigger)
{
	for (auto crate : crates_)
	{
		kill_trigger->add_collision_test(crate);
	}
}
