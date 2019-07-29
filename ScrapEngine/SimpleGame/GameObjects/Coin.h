#pragma once

#include "Engine/LogicCore/GameObject/SGameObject.h"
#include "Engine/LogicCore/Manager/LogicManagerView.h"

class Coin : public ScrapEngine::Core::SGameObject
{
private:
	//Utils
	ScrapEngine::Core::LogicManagerView* logic_manager_view_ = nullptr;
	ScrapEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	//Mesh
	ScrapEngine::Core::MeshComponent* mesh_ = nullptr;
	//Trigger
	ScrapEngine::Core::TriggerComponent* box_trigger_ = nullptr;
	ScrapEngine::Core::RigidBodyComponent* test_collision_object_ = nullptr;
	//Audio
	ScrapEngine::Core::AudioComponent3D* coin_sound_ = nullptr;
	bool sound_started_ = false;
public:
	Coin(ScrapEngine::Core::LogicManagerView* logic_manager_ref, const ScrapEngine::Core::SVector3& start_pos);
	~Coin() = default;

	void set_collision_test(SGameObject* obj, int index = 1);

	void game_update(float time) override;
};
