#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace ScrapEngine
{
	namespace Core
	{
		class MeshComponent;
		class RigidBodyComponent;
		class ComponentsManager;
	}
}

namespace ScrapEngine
{
	namespace Input
	{
		class InputManager;
	}
}

class Ball : public ScrapEngine::Core::SGameObject
{
private:
	//Utils
	ScrapEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	ScrapEngine::Input::InputManager* input_manager_ref_ = nullptr;
	//Collider
	ScrapEngine::Core::RigidBodyComponent* collider_ = nullptr;
	//Mesh
	ScrapEngine::Core::MeshComponent* mesh_ = nullptr;
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
	bool get_can_move() const;
	void set_spawnpoint(const ScrapEngine::Core::SVector3& pos);

	ScrapEngine::Core::SVector3 get_rigidbody_location() const;
private:
	bool is_on_ground() const;
};
