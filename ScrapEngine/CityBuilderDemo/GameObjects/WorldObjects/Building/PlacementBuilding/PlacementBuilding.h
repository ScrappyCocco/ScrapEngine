#pragma once

#include "../BaseBuilding.h"


class PlacementBuilding : public BaseBuilding
{
public:
	PlacementBuilding(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
		const ScrapEngine::Core::SVector3& start_pos,
		const ScrapEngine::Core::SVector3& size = ScrapEngine::Core::SVector3(1.5f, 1.5f, 1.5f));
	~PlacementBuilding() = default;

	void set_visible(bool visible) const;
};

