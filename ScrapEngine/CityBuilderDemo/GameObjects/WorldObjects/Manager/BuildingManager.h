#pragma once

#include "../Building/BaseBuilding.h"
#include "../Building/PlacementBuilding/PlacementBuilding.h"

class BuildingManager
{
private:
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_manager_view_ = nullptr;
	ScrapEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;

	PlacementBuilding* placement_building_;
	std::vector<BaseBuilding*> buildings_;
public:
	BuildingManager(ScrapEngine::Core::LogicManagerView* logic_manager_ref);
	~BuildingManager() = default;

	PlacementBuilding* get_placement_building() const;
	void add_building(const ScrapEngine::Core::SVector3& pos);
};

