#include <Engine/Rendering/Camera/Camera.h>
#include <glm/gtx/quaternion.hpp>

ScrapEngine::Render::Camera::Camera(const float input_min_draw_distance, const float input_max_draw_distance)
	: camera_location_(Core::SVector3(0.f, 0.f, 1.f))
{
	min_draw_distance_ = input_min_draw_distance;
	max_draw_distance_ = input_max_draw_distance;

	yaw_ = -90.0f;
	pitch_ = 0.0f;
}

void ScrapEngine::Render::Camera::set_camera_location(const Core::SVector3& new_camera_location)
{
	camera_location_ = new_camera_location;
}

void ScrapEngine::Render::Camera::execute_camera_update()
{
	update_camera_vectors();
	//Ri-generate look matrix
	generate_look_matrix();
	//Update view frustum
	update_frustum();
}

void ScrapEngine::Render::Camera::process_mouse_movement(const float xpos, const float ypos, const bool constrain_pitch)
{
	if (first_mouse_read_)
	{
		first_mouse_read_ = false;
		last_x_ = xpos;
		last_y_ = ypos;
	}
	float xoffset = xpos - last_x_;
	float yoffset = last_y_ - ypos; // reversed since y-coordinates range from bottom to top
	last_x_ = xpos;
	last_y_ = ypos;

	xoffset *= mouse_sensivity_;
	yoffset *= mouse_sensivity_;

	yaw_ += xoffset;
	pitch_ += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrain_pitch)
	{
		if (pitch_ > 89.0f)
			pitch_ = 89.0f;
		if (pitch_ < -89.0f)
			pitch_ = -89.0f;
	}
}

void ScrapEngine::Render::Camera::update_camera_vectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(-pitch_));
	camera_front_ = normalize(front);
}

void ScrapEngine::Render::Camera::set_mouse_sensivity(const float new_sensivity)
{
	mouse_sensivity_ = new_sensivity;
}

void ScrapEngine::Render::Camera::set_min_render_distance(const float new_render_distance)
{
	min_draw_distance_ = new_render_distance;
	//Update projection matrix
	generate_projection_matrix();
}

void ScrapEngine::Render::Camera::set_max_render_distance(float new_render_distance)
{
	max_draw_distance_ = new_render_distance;
	//Update projection matrix
	generate_projection_matrix();
}

float ScrapEngine::Render::Camera::get_camera_yaw() const
{
	return yaw_;
}

float ScrapEngine::Render::Camera::get_camera_pitch() const
{
	return pitch_;
}

float ScrapEngine::Render::Camera::get_camera_roll() const
{
	return roll_;
}

void ScrapEngine::Render::Camera::set_camera_yaw(const float yaw)
{
	yaw_ = yaw;
}

void ScrapEngine::Render::Camera::set_camera_pitch(const float pitch)
{
	pitch_ = pitch;
}

void ScrapEngine::Render::Camera::set_camera_roll(const float roll)
{
	roll_ = roll;
}

float ScrapEngine::Render::Camera::get_mouse_sensivity() const
{
	return mouse_sensivity_;
}

float ScrapEngine::Render::Camera::get_camera_min_draw_distance() const
{
	return min_draw_distance_;
}

float ScrapEngine::Render::Camera::get_camera_max_draw_distance() const
{
	return max_draw_distance_;
}

ScrapEngine::Core::SVector3 ScrapEngine::Render::Camera::get_camera_front() const
{
	return Core::SVector3(camera_front_);
}

ScrapEngine::Core::SVector3 ScrapEngine::Render::Camera::get_camera_up() const
{
	return Core::SVector3(camera_up_);
}

ScrapEngine::Core::SVector3 ScrapEngine::Render::Camera::get_camera_location() const
{
	return camera_location_;
}

float ScrapEngine::Render::Camera::get_camera_fov() const
{
	return fov_;
}

void ScrapEngine::Render::Camera::set_camera_fov(const float fov)
{
	fov_ = fov;
	//Update projection matrix
	generate_projection_matrix();
}

glm::mat4 ScrapEngine::Render::Camera::get_camera_projection_matrix() const
{
	return projection_matrix_;
}

glm::mat4 ScrapEngine::Render::Camera::get_camera_look_matrix() const
{
	return look_matrix_;
}

void ScrapEngine::Render::Camera::set_swap_chain_extent(const vk::Extent2D& swap_chain_extent)
{
	swap_chain_extent_ = swap_chain_extent;
	generate_matrices();
}

void ScrapEngine::Render::Camera::update_frustum()
{
	frustum_.update(projection_matrix_ * look_matrix_);
}

void ScrapEngine::Render::Camera::generate_matrices()
{
	generate_projection_matrix();
	generate_look_matrix();
}

void ScrapEngine::Render::Camera::generate_projection_matrix()
{
	//Perspective stuff
	projection_matrix_ = glm::perspective(glm::radians(fov_),
	                                      swap_chain_extent_.width / static_cast<float>(swap_chain_extent_.height),
	                                      min_draw_distance_,
	                                      max_draw_distance_);
	//Invert image for openGL style
	projection_matrix_[1][1] *= -1;
}

void ScrapEngine::Render::Camera::generate_look_matrix()
{
	look_matrix_ = lookAt(camera_location_.get_glm_vector(),
	                      camera_location_.get_glm_vector() + camera_front_,
	                      camera_up_);
}

bool ScrapEngine::Render::Camera::frustum_check_sphere(const glm::vec3& pos, const float radius)
{
	return frustum_.check_sphere(pos, radius);
}
