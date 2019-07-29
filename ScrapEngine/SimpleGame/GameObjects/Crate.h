#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Manager/LogicManagerView.h"

class Crate : public ScrapEngine::Core::SGameObject
{
private:
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_manager_view_ = nullptr;
	ScrapEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	//Mesh
	ScrapEngine::Core::MeshComponent* mesh_;
	//Collider
	ScrapEngine::Core::RigidBodyComponent* box_collider_;
public:
	Crate(ScrapEngine::Core::LogicManagerView* logic_manager_ref, const ScrapEngine::Core::SVector3& start_pos);
	~Crate() = default;

	void die() override;
};

