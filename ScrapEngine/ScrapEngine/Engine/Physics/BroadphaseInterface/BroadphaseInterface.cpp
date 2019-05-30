#include <Engine/Physics/BroadphaseInterface/BroadphaseInterface.h>

ScrapEngine::Physics::BroadphaseInterface::BroadphaseInterface()
{
	overlapping_pair_cache_ = new btDbvtBroadphase();
}

ScrapEngine::Physics::BroadphaseInterface::~BroadphaseInterface()
{
	delete overlapping_pair_cache_;
}

btBroadphaseInterface* ScrapEngine::Physics::BroadphaseInterface::get_broadphase_interface() const
{
	return overlapping_pair_cache_;
}

