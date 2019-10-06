#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/LogicCore/Manager/LogicManagerView.h>

class BaseBuilding : public ScrapEngine::Core::SGameObject
{
protected:
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_manager_view_ = nullptr;
	ScrapEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	//Mesh
	ScrapEngine::Core::MeshComponent* mesh_ = nullptr;
public:
	enum class color
	{
		white,
		green,
		yellow,
		grey,
		dark_grey
	};
	
	BaseBuilding(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
		const ScrapEngine::Core::SVector3& start_pos,
		const ScrapEngine::Core::SVector3& size = ScrapEngine::Core::SVector3(1.5f, 1.5f, 1.5f),
		color c = color::white
	);

	//Used to destroy the building
	void die() override;
	
	virtual ~BaseBuilding();
};

