#include "WorldObjectsCreator.h"
#include "Crate.h"
#include "Coin.h"

void WorldObjectsCreator::create_crate(const ScrapEngine::Core::SVector3& pos)
{
	crates_.push_back(new Crate(logic_manager_ref_, pos));
}

void WorldObjectsCreator::create_coin(const ScrapEngine::Core::SVector3& pos) const
{
	Coin* coin = new Coin(logic_manager_ref_, pos);
	coin->set_collision_test(player_ref_);
	logic_manager_ref_->register_game_object(coin);
}

void WorldObjectsCreator::create_crates()
{
	// First group
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(70, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(80, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(60, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(75, 10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(65, 10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(70, 20, -50)));
	// Second group
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-70, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-80, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-60, 0, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-75, 10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-65, 10, -50)));
	crates_.push_back(new Crate(logic_manager_ref_, ScrapEngine::Core::SVector3(-70, 20, -50)));
}

void WorldObjectsCreator::create_coins() const
{
	create_coin(ScrapEngine::Core::SVector3(0, -10, -150));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -200));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -250));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -300));
	create_coin(ScrapEngine::Core::SVector3(0, -10, -350));
}

WorldObjectsCreator::WorldObjectsCreator(ScrapEngine::Core::LogicManagerView* logic_manager_ref, ScrapEngine::Core::SGameObject* player)
	: logic_manager_ref_(logic_manager_ref), player_ref_(player)
{
	create_crates();
	create_coins();
}

void WorldObjectsCreator::register_crates_to_trigger(Trigger* kill_trigger)
{
	for (auto crate : crates_)
	{
		kill_trigger->add_collision_test(crate);
	}
}
