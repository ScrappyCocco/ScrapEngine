#pragma once

#include <glm/glm.hpp>
#include "../../Utility/UsefulTypes.h"

namespace ScrapEngine {

	class Camera
	{
		glm::vec3 cameraLocation;

		float minDrawDistance, maxDrawDistance;

		float Yaw;
		float Pitch;

		float mouseSensivity = 0.05f;
		float lastX = 400, lastY = 300;
		bool firstMouseRead = true;
		//Cache values
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraRight;
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		virtual void updateCameraVectors();
	public:
		Camera(glm::vec3 input_cameraLocation = glm::vec3(0.0f, 0.0f, 1.0f), float input_minDrawDistance = 0.1f, float input_maxDrawDistance = 100.f);
		~Camera() = default;

		virtual void ProcessMouseMovement(float xpos, float ypos, bool constrainPitch = true);

		void setCameraLocation(glm::vec3 newCameraLocation);
		void setMouseSensivity(float newSensivity);
		void setMinRenderDistance(float newRenderDistance);
		void setMaxRenderDistance(float newRenderDistance);

		float getMouseSensivity();
		float getCameraMinDrawDistance() const;
		float getCameraMaxDrawDistance() const;
		glm::vec3 getCameraFront() const;
		glm::vec3 getCameraUp() const;
		glm::vec3 getCameraLocation() const;
	};

}

