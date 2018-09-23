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

		vk::Device* deviceRef;
	public:
		VertexBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<ScrapEngine::Vertex>* vertices, vk::CommandPool* commandPool, vk::Queue* graphicsQueue);
		~VertexBuffer();

		vk::Buffer* getVertexBuffer();
	};

}

