#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <array>

namespace ScrapEngine
{
	namespace Render
	{
		class Vertex
		{
		public:
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 tex_coord;
			glm::vec3 normal;

			static vk::VertexInputBindingDescription get_binding_description();

			static std::array<vk::VertexInputAttributeDescription, 4> get_attribute_descriptions();
		};

		class OffscreenVertex
		{
		public:
			glm::vec3 pos;

			static vk::VertexInputBindingDescription get_binding_description();

			static std::array<vk::VertexInputAttributeDescription, 1> get_attribute_descriptions();
		};
	}
}
