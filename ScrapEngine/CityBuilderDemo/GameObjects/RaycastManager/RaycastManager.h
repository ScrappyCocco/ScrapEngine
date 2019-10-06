#pragma once

#include <Engine/Rendering/Manager/RenderManager.h>
#include "../WorldObjects/Manager/BuildingManager.h"

class RaycastManager
{
private:
	ScrapEngine::Render::Camera* game_camera_ref_ = nullptr;
	ScrapEngine::Core::RigidBodyComponent* world_terrain_collider_ = nullptr;
	ScrapEngine::Core::ComponentsManager* component_manager_ = nullptr;

	BuildingManager* building_manager_ = nullptr;
	PlacementBuilding* placement_building_ = nullptr;

	float window_width_, window_height_;

	ScrapEngine::Core::SVector3 convert_mouse_position(float mouse_x, float mouse_y) const;
	float round(float value, int to = 5) const;
public:
	RaycastManager(ScrapEngine::Render::Camera* input_game_camera_ref,
	               ScrapEngine::Core::RigidBodyComponent* input_world_terrain_collider,
	               ScrapEngine::Core::ComponentsManager* input_component_manager,
	               float window_width, float window_height);
	~RaycastManager() = default;

	void set_building_manager(BuildingManager* input_building_manager_ref);

	void mouse_movement(double mouse_x, double mouse_y);
	void mouse_click(double mouse_x, double mouse_y);
};
