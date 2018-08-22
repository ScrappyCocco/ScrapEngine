#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "../../Base/Vertex.h"

namespace ScrapEngine {

	class IndexBuffer
	{
	private:
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		VkDevice deviceRef;
	public:
		IndexBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, const std::vector<uint32_t>* indices, VkCommandPool commandPool, VkQueue graphicsQueue);
		~IndexBuffer();

		VkBuffer getIndexBuffer() const;
	};

}

