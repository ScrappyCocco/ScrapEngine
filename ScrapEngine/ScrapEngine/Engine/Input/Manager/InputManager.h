#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace ScrapEngine
{
	namespace Input
	{
		struct mouse_location
		{
			const double xpos, ypos;

			mouse_location() : xpos(0), ypos(0)
			{
			}

			mouse_location(const double x, const double y) : xpos(x), ypos(y)
			{
			}
		};

		enum class cursor_mode
		{
			/**
			 * \brief makes the cursor visible and behaving normally.
			 */
			cursor_normal_mode = GLFW_CURSOR_NORMAL,
			/**
			 * \brief makes the cursor invisible when it is over the client area of the window but does not restrict the cursor from leaving.
			 */
			cursor_hidden_mode = GLFW_CURSOR_HIDDEN,
			/**
			 * \brief hides and grabs the cursor, providing virtual and unlimited cursor movement.
			 */
			cursor_grabbed_mode = GLFW_CURSOR_DISABLED
		};

		enum class system_cursor_shapes
		{
			cursor_regular_arrow = GLFW_ARROW_CURSOR,
			cursor_crosshair_shape = GLFW_CROSSHAIR_CURSOR,
			cursor_hand_shape = GLFW_HAND_CURSOR,
			cursor_horizontal_resize_arrow_shape = GLFW_HRESIZE_CURSOR,
			cursor_vertical_resize_arrow_shape = GLFW_VRESIZE_CURSOR,
			cursor_input_beam_shape = GLFW_IBEAM_CURSOR
		};

		enum class button_state
		{
			released,
			pressed
		};

		enum class scroll_status
		{
			scroll_up,
			scroll_down,
			scroll_still
		};

		class InputManager
		{
		private:
			GLFWwindow* window_ref_;
			GLFWcursor* cursor_ = nullptr;

			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
			static scroll_status scroll_status_;
		public:
			explicit InputManager(GLFWwindow* input_window_ref);
			InputManager(const InputManager&) = delete;
			InputManager& operator =(const InputManager&) = delete;
			InputManager(InputManager&&) = delete;
			InputManager& operator=(InputManager&&) = delete;
			~InputManager();

			mouse_location get_last_mouse_location() const;
			void set_cursor_input_mode(cursor_mode new_mode) const;

			void load_new_cursor(const std::string& path_to_file, int xhot = 0, int yhot = 0);
			void load_system_cursor(const system_cursor_shapes& new_shape);
			void reset_cursor_to_system_default();

			button_state get_keyboard_key_status(int key_to_check) const;
			bool get_keyboard_key_pressed(int key_to_check) const;
			bool get_keyboard_key_released(int key_to_check) const;

			button_state get_mouse_button_status(int button_to_check) const;
			bool get_mouse_button_pressed(int button_to_check) const;
			bool get_mouse_button_released(int button_to_check) const;

			scroll_status get_mouse_scroll_status() const;
		};
	}
}
