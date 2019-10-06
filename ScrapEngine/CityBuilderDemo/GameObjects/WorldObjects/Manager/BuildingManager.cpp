#include "BuildingManager.h"
#include "../Building/StandardBuilding/StandardBuilding.h"

BuildingManager::BuildingManager(ScrapEngine::Core::LogicManagerView* logic_manager_ref)
	: logic_manager_view_(logic_manager_ref),
	  component_manager_ref_(logic_manager_ref->get_components_manager())
{
	placement_building_ = new PlacementBuilding(logic_manager_view_,
	                                            ScrapEngine::Core::SVector3(0, 0, 0),
	                                            ScrapEngine::Core::SVector3(1, 1, 1));

	placement_building_->set_visible(false);
}

PlacementBuilding* BuildingManager::get_placement_building() const
{
	return placement_building_;
}

void BuildingManager::add_building(const ScrapEngine::Core::SVector3& pos)
{
	BaseBuilding* new_building = new StandardBuilding(logic_manager_view_,
	                                                  pos,
	                                                  ScrapEngine::Core::SVector3(1, 1, 1));

	buildings_.push_back(new_building);
}
