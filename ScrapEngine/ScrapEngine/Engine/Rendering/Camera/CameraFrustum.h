#pragma once

/*
* View frustum culling class
*
* Copyright (C) 2016 by Sascha Willems - www.saschawillems.de
*
* For more informations see https://github.com/SaschaWillems/Vulkan
*/

#include <glm/vec4.hpp>
#include <array>
#include <glm/mat4x4.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class CameraFrustum
		{
		private:
			enum side { LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3, BACK = 4, FRONT = 5 };

			std::array<glm::vec4, 6> planes_;
		public:
			CameraFrustum() = default;
			~CameraFrustum() = default;

			void update(const glm::mat4& matrix);

			bool check_sphere(const glm::vec3& pos, float radius);
		};
	}
}
