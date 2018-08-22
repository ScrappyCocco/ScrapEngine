#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "../Base/Vertex.h"

namespace ScrapEngine {

	class VulkanModel
	{
	private:
		const std::string MODEL_PATH;
		const std::string TEXTURE_PATH;

		std::vector<ScrapEngine::Vertex> vertices;
		std::vector<uint32_t> indices;
	public:
		VulkanModel(std::string input_MODEL_PATH, std::string input_TEXTURE_PATH);
		~VulkanModel();

		const std::vector<ScrapEngine::Vertex>* getVertices();
		const std::vector<uint32_t>* getIndices();
	};

}

