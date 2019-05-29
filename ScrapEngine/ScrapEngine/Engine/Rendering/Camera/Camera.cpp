#include <Engine/Rendering/Camera/Camera.h>
#include <glm/detail/func_trigonometric.inl>
#include <glm/detail/func_geometric.inl>

ScrapEngine::Render::Camera::Camera(float input_min_draw_distance, float input_max_draw_distance)
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

void ScrapEngine::Render::Camera::process_mouse_movement(float xpos, float ypos, bool constrain_pitch)
{
	if (first_mouse_read_)
	{
		first_mouse_read_ = false;
		last_x_ = xpos;
		lastY = ypos;
	}
	float xoffset = xpos - last_x_;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	last_x_ = xpos;
	lastY = ypos;

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

	update_camera_vectors();
}

void ScrapEngine::Render::Camera::update_camera_vectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(-pitch_));
	camera_front_ = glm::normalize(front);
}

void ScrapEngine::Render::Camera::set_mouse_sensivity(float new_sensivity)
{
	mouse_sensivity_ = new_sensivity;
}

void ScrapEngine::Render::Camera::set_min_render_distance(float new_render_distance)
{
	min_draw_distance_ = new_render_distance;
}

void ScrapEngine::Render::Camera::set_max_render_distance(float new_render_distance)
{
	max_draw_distance_ = new_render_distance;
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
