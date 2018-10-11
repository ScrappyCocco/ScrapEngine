#pragma once

#include <glm/glm.hpp>
#include "../../Utility/UsefulTypes.h"

namespace ScrapEngine {

	class Camera
	{
		ScrapEngine::Transform CameraTransform;
		glm::vec3 cameraTarget;

		float minDrawDistance, maxDrawDistance;

		float Yaw;
		float Pitch;

		float mouseSensivity = 0.05f;

		//Cache values
		glm::vec3 cameraDirection;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;

		void updateCameraVectors();
	public:
		Camera(ScrapEngine::Transform input_CameraTransform = ScrapEngine::Transform(), glm::vec3 input_cameraTarget = glm::vec3(0.0f, 0.0f, 1.0f), float input_minDrawDistance = 0.1f, float input_maxDrawDistance = 100.f);
		~Camera() = default;

		void setCameraTransform(ScrapEngine::Transform input_CameraTransform);
		void setCameraLocation(glm::vec3 location);
		void setCameraRotation(glm::vec3 rotation);
		void setCameraTarget(glm::vec3 target);
		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		void setMouseSensivity(float newSensivity);

		float getMouseSensivity();
		float getCameraMinDrawDistance() const;
		float getCameraMaxDrawDistance() const;
		glm::vec3 getCameraFront() const;
		glm::vec3 getCameraUp() const;
		ScrapEngine::Transform getCameraTransform() const;
		glm::vec3 getCameraTarget() const;
		glm::vec3 getCameraDirection() const;
	};

}

