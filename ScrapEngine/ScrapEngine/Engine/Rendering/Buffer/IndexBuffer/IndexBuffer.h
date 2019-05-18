#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../Base/Vertex.h"

namespace ScrapEngine {
	namespace Render {
		class IndexBuffer
		{
		private:
			vk::Buffer indexBuffer;
			vk::DeviceMemory indexBufferMemory;
		public:
			IndexBuffer(const std::vector<uint32_t>* indices);
			~IndexBuffer();

			vk::Buffer* getIndexBuffer();
		};
	}
}

