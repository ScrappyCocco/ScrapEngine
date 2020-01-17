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
	class Vertex
	{
	public:
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 tex_coord;
		glm::vec3 normal;

		static vk::VertexInputBindingDescription get_binding_description()
		{
			const vk::VertexInputBindingDescription
				binding_description(0, sizeof(Vertex), vk::VertexInputRate::eVertex);

			return binding_description;
		}

		static std::array<vk::VertexInputAttributeDescription, 4> get_attribute_descriptions()
		{
			const std::array<vk::VertexInputAttributeDescription, 4> attribute_descriptions = {
				vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
				vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color)),
				vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, tex_coord)),
				vk::VertexInputAttributeDescription(3, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, normal)),
			};

			return attribute_descriptions;
		}
	};
}
