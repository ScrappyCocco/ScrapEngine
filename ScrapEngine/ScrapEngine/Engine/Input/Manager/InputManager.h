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

		enum cursor_mode
		{
			/**
			 * \brief makes the cursor visible and behaving normally.
			 */
			cursor_normal_mode,
			/**
			 * \brief makes the cursor invisible when it is over the client area of the window but does not restrict the cursor from leaving.
			 */
			cursor_hidden_mode,
			/**
			 * \brief hides and grabs the cursor, providing virtual and unlimited cursor movement.
			 */
			cursor_grabbed_mode
		};

		enum system_cursor_shapes
		{
			cursor_regular_arrow,
			cursor_crosshair_shape,
			cursor_hand_shape,
			cursor_horizontal_resize_arrow_shape,
			cursor_vertical_resize_arrow_shape,
			cursor_input_beam_shape
		};

		enum button_state
		{
			released,
			pressed
		};

		enum scroll_status
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

			Input::mouse_location get_last_mouse_location() const;
			void set_cursor_input_mode(Input::cursor_mode new_mode) const;

			void load_new_cursor(const std::string& path_to_file, int xhot = 0, int yhot = 0);
			void load_system_cursor(const Input::system_cursor_shapes& new_shape);
			void reset_cursor_to_system_default();

			Input::button_state get_keyboard_key_status(int key_to_check) const;
			bool get_keyboard_key_pressed(int key_to_check) const;
			bool get_keyboard_key_released(int key_to_check) const;

			Input::button_state get_mouse_button_status(int button_to_check) const;
			bool get_mouse_button_pressed(int button_to_check) const;
			bool get_mouse_button_released(int button_to_check) const;

			scroll_status get_mouse_scroll_status() const;
		};
	}
}
