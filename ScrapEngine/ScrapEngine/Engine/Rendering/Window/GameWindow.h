#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Engine/Input/Manager/InputManager.h>
#include <string>

namespace ScrapEngine
{
	namespace Render
	{
		class GameWindow
		{
			friend class VulkanSurface;

		private:
			const uint32_t width_ = 800;
			const uint32_t height_ = 600;
			const std::string window_title_ = "ScrapEngine Game";

			GLFWwindow* window_; //actual window reference

		public:
			GameWindow(uint32_t input_width = 800, uint32_t input_height = 600,
			           std::string input_window_title = "ScrapEngine Game");
			~GameWindow();

			void initialize_window();

			void set_window_size(int input_width, int input_height) const;
			void set_window_title(const std::string& title) const;
			void set_window_icon(const std::string& path_to_file) const;

			void close_window() const;

			ScrapEngine::Input::InputManager* create_window_input_manager() const;

			bool check_window_should_close() const;
		};
	}
}
