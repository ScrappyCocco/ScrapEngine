#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>
#include <Engine/Rendering/Camera/CameraFrustum.h>

namespace ScrapEngine
{
	namespace Render
	{
		class Camera
		{
		private:
			Core::SVector3 camera_location_;
			CameraFrustum frustum_;
			vk::Extent2D swap_chain_extent_;

			//Camera matrices
			glm::mat4 projection_matrix_;
			glm::mat4 look_matrix_;

			float min_draw_distance_, max_draw_distance_;

			//X rotation
			float pitch_ = 0;
			//Y rotation
			float yaw_ = 0;
			//Z rotation
			float roll_ = 0;

			//Camera fov
			float fov_ = 45.0f;

			//Free mouse look values
			float mouse_sensivity_ = 0.05f;
			float last_x_ = 400, last_y_ = 300;
			bool first_mouse_read_ = true;

			//Current view values
			glm::vec3 camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

			bool projection_matrix_dirty_ = true;
			bool look_matrix_dirty_ = true;

			virtual void update_camera_vectors();
			virtual void update_frustum();
			void generate_matrices();
			void generate_projection_matrix();
			void generate_look_matrix();
		public:
			Camera(float input_min_draw_distance = 0.1f,
			       float input_max_draw_distance = 100.f);
			virtual ~Camera() = default;

			void execute_camera_update();

			virtual void process_mouse_movement(float xpos, float ypos, bool constrain_pitch = true);

			void set_camera_location(const Core::SVector3& new_camera_location);
			void set_mouse_sensivity(float new_sensivity);
			void set_min_render_distance(float new_render_distance);
			void set_max_render_distance(float new_render_distance);

			float get_camera_yaw() const;
			float get_camera_pitch() const;
			float get_camera_roll() const;
			void set_camera_yaw(float yaw);
			void set_camera_pitch(float pitch);
			void set_camera_roll(float roll);

			bool get_projection_matrix_dirty() const;
			bool get_look_matrix_dirt() const;
			void cancel_dirty_matrix();

			float get_mouse_sensivity() const;
			float get_camera_min_draw_distance() const;
			float get_camera_max_draw_distance() const;
			Core::SVector3 get_camera_front() const;
			Core::SVector3 get_camera_up() const;
			Core::SVector3 get_camera_location() const;

			float get_camera_fov() const;
			void set_camera_fov(float fov);

			float get_camera_aspect_ratio() const;

			glm::mat4 get_camera_projection_matrix() const;
			glm::mat4 get_camera_look_matrix() const;

			void set_swap_chain_extent(const vk::Extent2D& swap_chain_extent);
			bool frustum_check_sphere(const glm::vec3& pos, float radius);
		};
	}
}
