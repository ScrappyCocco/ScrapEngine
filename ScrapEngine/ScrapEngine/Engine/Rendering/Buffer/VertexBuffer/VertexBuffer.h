#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../Base/Vertex.h"

namespace ScrapEngine {

	class VertexBuffer
	{
	private:
		vk::Buffer vertexBuffer;
		vk::DeviceMemory vertexBufferMemory;
	public:
		VertexBuffer(const std::vector<ScrapEngine::Vertex>* vertices);
		~VertexBuffer();

		vk::Buffer* getVertexBuffer();
	};

}

