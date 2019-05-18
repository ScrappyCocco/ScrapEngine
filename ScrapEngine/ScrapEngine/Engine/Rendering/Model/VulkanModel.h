#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include <vector>
#include "../Base/Vertex.h"

namespace ScrapEngine {
	namespace Render {
		class VulkanModel
		{
		private:
			std::vector<ScrapEngine::Vertex> vertices;
			std::vector<uint32_t> indices;
		public:
			VulkanModel(const std::string& input_MODEL_PATH);
			~VulkanModel();

			const std::vector<ScrapEngine::Vertex>* getVertices();
			const std::vector<uint32_t>* getIndices();
		};
	}
}

