#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace ScrapEngine
{
	namespace Core
	{
		class RigidBodyComponent;
		class MeshComponent;
		class ComponentsManager;
		class LogicManagerView;
	}
}

class Crate final : public ScrapEngine::Core::SGameObject
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
	Crate(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
	      const ScrapEngine::Core::SVector3& start_pos,
	      const ScrapEngine::Core::SVector3& size = ScrapEngine::Core::SVector3(1.5f, 1.5f, 1.5f),
	      float mass = 2.5f);
	~Crate() = default;

	void die() override;
};
