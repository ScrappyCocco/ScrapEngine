#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../Base/Vertex.h"

namespace ScrapEngine {
	class IndexBuffer
	{
	private:
		vk::Buffer indexBuffer;
		vk::DeviceMemory indexBufferMemory;

		vk::Device* deviceRef;
	public:
		IndexBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<uint32_t>* indices, vk::CommandPool* commandPool, vk::Queue* graphicsQueue);
		~IndexBuffer();

		vk::Buffer* getIndexBuffer();
	};

}

