#pragma once

#include "../BaseBuilding.h"

class StandardBuilding : public BaseBuilding
{
private:
	//Collider
	ScrapEngine::Core::RigidBodyComponent* box_collider_;
public:
	StandardBuilding(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
		const ScrapEngine::Core::SVector3& start_pos,
		const ScrapEngine::Core::SVector3& size = ScrapEngine::Core::SVector3(1.5f, 1.5f, 1.5f));
	~StandardBuilding() = default;

	void die() override;
};

