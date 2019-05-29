#pragma once

#include <string>

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
}
