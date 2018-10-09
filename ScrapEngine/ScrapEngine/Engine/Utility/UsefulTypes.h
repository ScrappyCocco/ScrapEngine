#pragma once

#include <string>
#include <glm/glm.hpp>

namespace ScrapEngine {
	struct game_base_info {
		std::string app_name;

		int app_version;
		uint32_t window_WIDTH, window_HEIGHT;

		bool window_fullscreen = false;

		game_base_info(std::string input_app_name, int input_app_version, uint32_t input_window_WIDTH, uint32_t input_window_HEIGHT, bool input_window_fullscreen)
			: app_name(input_app_name), app_version(input_app_version), window_WIDTH(input_window_WIDTH), window_HEIGHT(input_window_HEIGHT), window_fullscreen(input_window_fullscreen)
		{}
	};

	struct Transform {
		glm::vec3 location = glm::vec3();
		glm::vec3 rotation = glm::vec3();
		glm::vec3 scale = glm::vec3(1, 1, 1);;
	};
}
