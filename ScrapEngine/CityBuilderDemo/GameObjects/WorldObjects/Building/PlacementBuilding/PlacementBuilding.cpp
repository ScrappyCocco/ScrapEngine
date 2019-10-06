#include "PlacementBuilding.h"

PlacementBuilding::PlacementBuilding(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
             const ScrapEngine::Core::SVector3& start_pos,
             const ScrapEngine::Core::SVector3& size)
	: BaseBuilding(logic_manager_ref, start_pos, size, color::yellow)
{
	
}

void PlacementBuilding::set_visible(const bool visible) const
{
	mesh_->set_is_visible(visible);
}
