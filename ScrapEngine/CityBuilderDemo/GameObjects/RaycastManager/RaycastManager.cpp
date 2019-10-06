#include "RaycastManager.h"
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Core::SVector3 RaycastManager::convert_mouse_position(float mouse_x, float mouse_y) const
{
	//See http://antongerdelan.net/opengl/raycasting.html

	float x = (2.0f * static_cast<float>(mouse_x)) / window_width_ - 1.f;
	float y = (2.0f * static_cast<float>(mouse_y)) / window_height_ - 1.f;
	glm::vec2 normalized_coords = glm::vec2(x, y);

	glm::vec4 clip_coords = glm::vec4(normalized_coords.x, normalized_coords.y, -1.0f, 1.0f);

	glm::mat4 inverted_projection = glm::inverse(game_camera_ref_->get_camera_projection_matrix());
	glm::vec4 eye_coords_temp = inverted_projection * clip_coords;
	glm::vec4 eye_coords = glm::vec4(eye_coords_temp.x, eye_coords_temp.y, -1.f, 0.f);

	glm::mat4 inverted_view = glm::inverse(game_camera_ref_->get_camera_look_matrix());
	glm::vec4 ray_world = inverted_view * eye_coords;
	glm::vec3 mouse_ray = glm::vec3(ray_world.x, ray_world.y, ray_world.z);
	mouse_ray = glm::normalize(mouse_ray);

	return ScrapEngine::Core::SVector3(mouse_ray);
}

float RaycastManager::round(const float value, const int to) const
{
	const int using_value = static_cast<int>(value);
	// Smaller multiple 
	const int a = using_value / to * to;

	// Larger multiple 
	const int b = static_cast<int>(a + to);

	// Return of closest of two 
	if (using_value - a > b - using_value)
	{
		return static_cast<float>(b);
	}
	return static_cast<float>(a);
}

RaycastManager::RaycastManager(ScrapEngine::Render::Camera* input_game_camera_ref,
                               ScrapEngine::Core::RigidBodyComponent* input_world_terrain_collider,
                               ScrapEngine::Core::ComponentsManager* input_component_manager,
                               const float window_width, const float window_height)
	: game_camera_ref_(input_game_camera_ref),
	  world_terrain_collider_(input_world_terrain_collider),
	  component_manager_(input_component_manager),
	  window_width_(window_width), window_height_(window_height)
{
	if(!input_world_terrain_collider)
	{
		throw std::runtime_error("[RaycastManager] Invalid world collider");
	}
}

void RaycastManager::set_building_manager(BuildingManager* input_building_manager_ref)
{
	building_manager_ = input_building_manager_ref;
	placement_building_ = building_manager_->get_placement_building();
	placement_building_->set_visible(true);
}

void RaycastManager::mouse_movement(const double mouse_x, const double mouse_y)
{
	const ScrapEngine::Core::SVector3 camera_pos = game_camera_ref_->get_camera_location();
	const ScrapEngine::Core::SVector3 mouse_ray = convert_mouse_position(
		static_cast<float>(mouse_x),
		static_cast<float>(mouse_y)
	);

	const ScrapEngine::Core::SVector3 ray_end = camera_pos + mouse_ray * 1000;

	const ScrapEngine::Core::raycast_result result = component_manager_->execute_single_raycast(camera_pos, ray_end);

	if (result.component_hit)
	{
		ScrapEngine::Core::SVector3 world_point = result.world_point;
		ScrapEngine::Core::SVector3 approximated =
			ScrapEngine::Core::SVector3(
				round(world_point.get_x(), 10),
				world_point.get_y(),
				round(world_point.get_z(), 10)
			);
		placement_building_->set_object_location(approximated);
	}
}

void RaycastManager::mouse_click(double mouse_x, double mouse_y)
{
	const ScrapEngine::Core::SVector3 camera_pos = game_camera_ref_->get_camera_location();
	const ScrapEngine::Core::SVector3 mouse_ray = convert_mouse_position(
		static_cast<float>(mouse_x),
		static_cast<float>(mouse_y)
	);

	const ScrapEngine::Core::SVector3 ray_end = camera_pos + mouse_ray * 1000;

	const ScrapEngine::Core::raycast_result result = component_manager_->execute_single_raycast(camera_pos, ray_end);

	if (result.component_hit)
	{
		ScrapEngine::Core::SVector3 world_point = result.world_point;
		ScrapEngine::Core::SVector3 approximated =
			ScrapEngine::Core::SVector3(
				round(world_point.get_x(), 10),
				world_point.get_y(),
				round(world_point.get_z(), 10)
			);
		building_manager_->add_building(approximated);
	}
}
