#include "Camera.h"

ScrapEngine::Camera::Camera(ScrapEngine::Transform input_CameraTransform, glm::vec3 input_cameraTarget, float input_minDrawDistance, float input_maxDrawDistance)
{
	CameraTransform = input_CameraTransform;
	cameraTarget = input_cameraTarget;
	minDrawDistance = input_minDrawDistance;
	maxDrawDistance = input_maxDrawDistance;

	Yaw = -90.0f;
	Pitch = 0.0f;
}

void ScrapEngine::Camera::setCameraTransform(ScrapEngine::Transform input_CameraTransform)
{
	CameraTransform = input_CameraTransform;
}

void ScrapEngine::Camera::setCameraLocation(glm::vec3 location)
{
	CameraTransform.location = location;
}

void ScrapEngine::Camera::setCameraRotation(glm::vec3 rotation)
{
	CameraTransform.rotation = rotation;
}

void ScrapEngine::Camera::setCameraTarget(glm::vec3 target)
{
	cameraTarget = target;
}

void ScrapEngine::Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
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
	front.z = sin(glm::radians(-Yaw)) * cos(glm::radians(Pitch));
	cameraFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void ScrapEngine::Camera::setMouseSensivity(float newSensivity)
{
	mouseSensivity = newSensivity;
}

float ScrapEngine::Camera::getMouseSensivity()
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
	return up;
}

ScrapEngine::Transform ScrapEngine::Camera::getCameraTransform() const
{
	return CameraTransform;
}

glm::vec3 ScrapEngine::Camera::getCameraTarget() const
{
	return cameraTarget;
}

glm::vec3 ScrapEngine::Camera::getCameraDirection() const
{
	return cameraDirection;
}
