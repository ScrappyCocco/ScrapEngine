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

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;
		static vk::VertexInputBindingDescription getBindingDescription() {
			vk::VertexInputBindingDescription bindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex);

			return bindingDescription;
		}

		static std::array<vk::VertexInputAttributeDescription, 3> getAttributeDescriptions() {
			std::array<vk::VertexInputAttributeDescription, 3> attributeDescriptions = {
				vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
				vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color)),
				vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, texCoord)),
			};

			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color && texCoord == other.texCoord;
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
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}