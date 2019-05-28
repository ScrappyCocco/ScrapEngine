#pragma once

#include <string>
#include <glm/vec3.hpp>

namespace ScrapEngine
{
	struct game_base_info
	{
		std::string app_name;

		int app_version;
		uint32_t window_width, window_height;

		bool window_fullscreen = false;
		bool vsync = true;

		game_base_info(const std::string& input_app_name, const int input_app_version,
		               const uint32_t input_window_width, const uint32_t input_window_height,
		               const bool input_window_fullscreen, const bool input_vsync)
			: app_name(input_app_name), app_version(input_app_version), window_width(input_window_width),
			  window_height(input_window_height), window_fullscreen(input_window_fullscreen), vsync(input_vsync)
		{
		}
	};

	struct Transform
	{
		glm::vec3 location = glm::vec3();
		glm::vec3 rotation = glm::vec3();
		glm::vec3 scale = glm::vec3(1, 1, 1);

		std::string to_string() const
		{
			return "Loc:(" + std::to_string(location.x) + ", " + std::to_string(location.y) + ", " + std::
				to_string(location.z) + "), " +
				"Rot:(" + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ", " + std::
				to_string(rotation.z) + "), " +
				"Scale:(" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ", " + std::to_string(scale.z) +
				")";
		}
	};
}
