#pragma once

#include <glm/glm.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class Camera
		{
			glm::vec3 camera_location_;

			float min_draw_distance_, max_draw_distance_;

			float yaw_;
			float pitch_;

			float mouse_sensivity_ = 0.05f;
			float last_x_ = 400, lastY = 300;
			bool first_mouse_read_ = true;
			//Cache values
			glm::vec3 camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 camera_right_;
			glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

			virtual void update_camera_vectors();
		public:
			Camera(glm::vec3 input_camera_location = glm::vec3(0.0f, 0.0f, 1.0f), float input_min_draw_distance = 0.1f,
			       float input_max_draw_distance = 100.f);
			~Camera() = default;

			virtual void process_mouse_movement(float xpos, float ypos, bool constrain_pitch = true);

			void set_camera_location(const glm::vec3& new_camera_location);
			void set_mouse_sensivity(float new_sensivity);
			void set_min_render_distance(float new_render_distance);
			void set_max_render_distance(float new_render_distance);

			float get_mouse_sensivity() const;
			float get_camera_min_draw_distance() const;
			float get_camera_max_draw_distance() const;
			glm::vec3 get_camera_front() const;
			glm::vec3 get_camera_up() const;
			glm::vec3 get_camera_location() const;
		};
	}
}
