#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "../../Base/Vertex.h"

namespace ScrapEngine {

	class VertexBuffer
	{
	private:
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;

		VkDevice deviceRef;
	public:
		VertexBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, const std::vector<ScrapEngine::Vertex>* vertices, VkCommandPool commandPool, VkQueue graphicsQueue);
		~VertexBuffer();

		VkBuffer getVertexBuffer() const;
	};

}

