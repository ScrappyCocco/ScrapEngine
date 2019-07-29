#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

class Ball : public ScrapEngine::Core::SGameObject
{
private:
	//Utils
	ScrapEngine::Core::ComponentsManager* component_manager_ref_;
	ScrapEngine::Input::InputManager* input_manager_ref_;
	//Collider
	ScrapEngine::Core::RigidBodyComponent* collider_;
	//Mesh
	ScrapEngine::Core::MeshComponent* mesh_;
	//Object utils vars
	ScrapEngine::Core::SVector3 respawn_point_;
	bool can_move_ = true;
public:
	Ball(ScrapEngine::Core::ComponentsManager* input_component_manager,
	               ScrapEngine::Input::InputManager* created_input_managerf);
	~Ball() = default;

	void game_update(float delta_time) override;
	void respawn() override;

	void set_can_move(bool can_move);
	void set_spawnpoint(const ScrapEngine::Core::SVector3& pos);
};
