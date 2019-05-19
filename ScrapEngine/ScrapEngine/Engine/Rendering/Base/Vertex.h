#pragma once

#include <vulkan/vulkan.hpp>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <array>

namespace ScrapEngine {

	class Vertex {
	public:
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 tex_coord;

		static vk::VertexInputBindingDescription get_binding_description() {
			const vk::VertexInputBindingDescription binding_description(0, sizeof(Vertex), vk::VertexInputRate::eVertex);

			return binding_description;
		}

		static std::array<vk::VertexInputAttributeDescription, 3> get_attribute_descriptions() {
			const std::array<vk::VertexInputAttributeDescription, 3> attribute_descriptions = {
				vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
				vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color)),
				vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, tex_coord)),
			};

			return attribute_descriptions;
		}

		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color && tex_coord == other.tex_coord;
		}
	};

	template <typename T>
	struct simple_buffer {
		vk::Buffer* buffer;
		const std::vector<T>* vectorData;

		simple_buffer(vk::Buffer* input_buffer, const std::vector<T>* input_vector)
			: buffer(input_buffer), vectorData(input_vector) {}
	};

}

namespace std {
	template<> struct hash<ScrapEngine::Vertex> {
		size_t operator()(ScrapEngine::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.tex_coord) << 1);
		}
	};
}