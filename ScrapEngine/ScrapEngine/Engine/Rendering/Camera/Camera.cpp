#include "Camera.h"

ScrapEngine::Camera::Camera(glm::vec3 input_cameraLocation, float input_minDrawDistance, float input_maxDrawDistance) : cameraLocation(input_cameraLocation)
{
	minDrawDistance = input_minDrawDistance;
	maxDrawDistance = input_maxDrawDistance;

	Yaw = -90.0f;
	Pitch = 0.0f;
}

void ScrapEngine::Camera::setCameraLocation(const glm::vec3& newCameraLocation)
{
	cameraLocation = newCameraLocation;
}

void ScrapEngine::Camera::ProcessMouseMovement(float xpos, float ypos, bool constrainPitch)
{
	if (firstMouseRead) {
		firstMouseRead = false;
		lastX = xpos;
		lastY = ypos;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	xoffset *= mouseSensivity;
	yoffset *= mouseSensivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void ScrapEngine::Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(-Pitch));
	cameraFront = glm::normalize(front);
}

void ScrapEngine::Camera::setMouseSensivity(float newSensivity)
{
	mouseSensivity = newSensivity;
}

void ScrapEngine::Camera::setMinRenderDistance(float newRenderDistance)
{
	minDrawDistance = newRenderDistance;
}

void ScrapEngine::Camera::setMaxRenderDistance(float newRenderDistance)
{
	maxDrawDistance = newRenderDistance;
}

float ScrapEngine::Camera::getMouseSensivity() const
{
	return mouseSensivity;
}

float ScrapEngine::Camera::getCameraMinDrawDistance() const
{
	return minDrawDistance;
}

float ScrapEngine::Camera::getCameraMaxDrawDistance() const
{
	return maxDrawDistance;
}

glm::vec3 ScrapEngine::Camera::getCameraFront() const
{
	return cameraFront;
}

glm::vec3 ScrapEngine::Camera::getCameraUp() const
{
	return cameraUp;
}

glm::vec3 ScrapEngine::Camera::getCameraLocation() const
{
	return cameraLocation;
}
